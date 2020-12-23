#include <gtest/gtest.h>
#include <TypesList.hpp>

#include <memory>

class A {
    public:
    using BASE_t = TL::Refine_R<TL::CreateTypesList_R<void>>;

    A() {}
    A(int a) {
        buffer << ' ' << a;
    }

    virtual void F1() = 0;

    protected:
    std::stringstream buffer;
};

class B : public A {
    public:
    using BASE_t = TL::Refine_R<TL::CreateTypesList_R<A, A::BASE_t>>;

    B() {}
    B(int a, int b)
        : A(a) {
        buffer << ' ' << b;
    }

    virtual void F1() override {
        std::cout << "class::B" << buffer.str() << std::endl;
    }
};

class C : public B {
    public:
    using BASE_t = TL::Refine_R<TL::CreateTypesList_R<B, B::BASE_t>>;

    C() {}
    C(int a, int b, int c)
        : B(a, b) {
        buffer << ' ' << c;
    }

    virtual void F1() override {
        std::cout << "class::C" << buffer.str() << std::endl;
    }
};

class D : public C {
    public:
    using BASE_t = TL::Refine_R<TL::CreateTypesList_R<C, C::BASE_t>>;

    D() {}
    D(int a, int b, int c, int d)
        : C(a, b, c) {
        buffer << ' ' << d;
    }

    virtual void F1() override {
        std::cout << "class::D" << buffer.str() << std::endl;
    }
};

TEST(Check_class_bases, test) {
    {
        using TClass = A;
        EXPECT_EQ(TClass::BASE_t::size, 1);
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, void>));
    }
    {
        using TClass = B;
        EXPECT_EQ(TClass::BASE_t::size, 2);
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, A>));
    }
    {
        using TClass = C;
        EXPECT_EQ(TClass::BASE_t::size, 3);
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, B>));
    }
    {
        using TClass = D;
        EXPECT_EQ(TClass::BASE_t::size, 4);
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, B>));
        EXPECT_TRUE((TL::IsInList_R<TClass::BASE_t, C>));
    }
}

// TT - Type to Type
template<class Type, class BASE_t>
struct T2T {
    std::shared_ptr<Type> value;
    using PossibleTo_t = BASE_t;
};

template<class To, class From, class... Arguments>
auto T2TMake(Arguments&&... arguments) {
    T2T<To, TL::Refine_R<TL::CreateTypesList_R<From, From::BASE_t>>> result{};
    result.value = std::make_shared<From>(arguments...);
    return result;
}

template<class BASE_t>
void AttemptUse(T2T<A, BASE_t> tb) {
    static_assert(TL::IsInList_R<BASE_t, C>, "this function can to use only with C-derivative params");
    tb.value->F1();
}

TEST(T2TMake, test) {
    {
        auto value = T2TMake<A, B>();
        using TClass = decltype(value)::PossibleTo_t;
        EXPECT_EQ(TClass::size, 3);
        EXPECT_TRUE((TL::IsInList_R<TClass, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass, B>));
        // AttemptUse(value); // compilation error
    }
    {
        auto value = T2TMake<A, B>(1, 2);
        using TClass = decltype(value)::PossibleTo_t;
        EXPECT_EQ(TClass::size, 3);
        EXPECT_TRUE((TL::IsInList_R<TClass, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass, B>));
        // AttemptUse(value); // compilation error
    }
    {
        auto value = T2TMake<A, C>();
        using TClass = decltype(value)::PossibleTo_t;
        EXPECT_EQ(TClass::size, 4);
        EXPECT_TRUE((TL::IsInList_R<TClass, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass, B>));
        EXPECT_TRUE((TL::IsInList_R<TClass, C>));
        AttemptUse(value);
    }
    {
        auto value = T2TMake<A, C>(1, 2, 3);
        using TClass = decltype(value)::PossibleTo_t;
        EXPECT_EQ(TClass::size, 4);
        EXPECT_TRUE((TL::IsInList_R<TClass, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass, B>));
        EXPECT_TRUE((TL::IsInList_R<TClass, C>));
        AttemptUse(value);
    }
    {
        auto value = T2TMake<A, D>();
        using TClass = decltype(value)::PossibleTo_t;
        EXPECT_EQ(TClass::size, 5);
        EXPECT_TRUE((TL::IsInList_R<TClass, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass, B>));
        EXPECT_TRUE((TL::IsInList_R<TClass, C>));
        EXPECT_TRUE((TL::IsInList_R<TClass, D>));
        AttemptUse(value);
    }
    {
        auto value = T2TMake<A, D>(1, 2, 3, 4);
        using TClass = decltype(value)::PossibleTo_t;
        EXPECT_EQ(TClass::size, 5);
        EXPECT_TRUE((TL::IsInList_R<TClass, void>));
        EXPECT_TRUE((TL::IsInList_R<TClass, A>));
        EXPECT_TRUE((TL::IsInList_R<TClass, B>));
        EXPECT_TRUE((TL::IsInList_R<TClass, C>));
        EXPECT_TRUE((TL::IsInList_R<TClass, D>));
        AttemptUse(value);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

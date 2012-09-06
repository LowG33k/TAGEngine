/*
 * Copyright (c) 2012 Loïc Marchand - loic.marchand73@gmail.com
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial applications,
 * and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original
 * software. If you use this software in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original
 * software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

// See header file.
inline Functor::Functor( IFunction* function ) : m_function( function )
{

}

// See header file.
inline std::string Functor::operator()( const std::string& params ) const
{
    return m_function->Execute( params );
}

// Use for return the base type.
// BaseType< int& > return a int for example.
template< typename T > struct BaseType { typedef T Type; };
template< typename T > struct BaseType< T& >{ typedef T Type; };
template< typename T > struct BaseType< const T >{ typedef T Type; };
template< typename T > struct BaseType< const T& >{ typedef T Type; };

/// \brief Use this struct for call standard function
///
/// \tparam ReturnType The return type of the function.
/// ////////////////////////////////////////////////
template< typename ReturnType >
struct CallFunction
{
    /// \brief Execute a free function with no parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \param function Function you want to use.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType >
    static std::string Execute( FunctionType function )
    {
        return StringBuilder( function() );
    }

    /// \brief Execute a free function with one parameter.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param Type of the param.
    /// \param function Function you want to use.
    /// \param param Param send to the function.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param >
    static std::string Execute( FunctionType function, Param param )
    {
        return StringBuilder( function( param ) );
    }

    /// \brief Execute a free function with two parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2 >
    static std::string Execute( FunctionType function, Param1 param1, Param2 param2 )
    {
        return StringBuilder( function( param1, param2 ) );
    }

    /// \brief Execute a free function with three parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \tparam Param3 Type of the third parameter.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    /// \param param3 Third param send to the function.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2, typename Param3 >
    static std::string Execute( FunctionType function, Param1 param1, Param2 param2, Param3 param3 )
    {
        return StringBuilder( function( param1, param2, param3 ) );
    }
};

/// \brief An overload for a function have void return type.
/// ////////////////////////////////////////////////
template< >
struct CallFunction< void >
{

    /// \brief Execute a free function with no parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \param function Function you want to use.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType >
    static std::string Execute( FunctionType function )
    {
        function();
        return "";
    }

    /// \brief Execute a free function with one parameter.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param Type of the param.
    /// \param function Function you want to use.
    /// \param param Param send to the function.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param >
    static std::string Execute( FunctionType function, Param param )
    {
        function( param );
        return "";
    }

    /// \brief Execute a free function with two parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2 >
    static std::string Execute( FunctionType function, Param1 param1, Param2 param2 )
    {
        function( param1, param2 );
        return "";
    }

    /// \brief Execute a free function with three parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \tparam Param3 Type of the third parameter.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    /// \param param3 Third param send to the function.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2, typename Param3 >
    static std::string Execute( FunctionType function, Param1 param1, Param2 param2, Param3 param3 )
    {
        function( param1, param2, param3 );
        return "";
    }
};


/// \brief Use this struct for call member function
///
/// \tparam ReturnType The return type of the function.
/// \tparam ObjectType The object type.
/// ////////////////////////////////////////////////
template< typename ReturnType, typename ObjectType >
struct CallMemberFunction
{

    /// \brief Execute a member function with no parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType >
    static std::string Execute( ObjectType object, FunctionType function )
    {
        return StringBuilder( (object.*function)() );
    }

    /// \brief Execute a member function with one parameter.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param Type of the param.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    /// \param param Param send to the function.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param >
    static std::string Execute( ObjectType object, FunctionType function, Param param )
    {
        return StringBuilder( (object.*function)( param ) );
    }

    /// \brief Execute a member function with two parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2 >
    static std::string Execute( ObjectType object, FunctionType function, Param1 param1, Param2 param2 )
    {
        return StringBuilder( (object.*function)( param1, param2 ) );
    }

    /// \brief Execute a member function with three parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \tparam Param3 Type of the third parameter.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    /// \param param3 Third param send to the function.
    ///
    /// \return The result of the function.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2, typename Param3 >
    static std::string Execute( ObjectType object, FunctionType function, Param1 param1, Param2 param2, Param3 param3 )
    {
        return StringBuilder( (object.*function)( param1, param2, param3 ) );
    }

};

/// \brief An overload for a function have void return type.
///
/// \tparam ObjectType The object type.
/// ////////////////////////////////////////////////
template< typename ObjectType >
struct CallMemberFunction< void, ObjectType >
{
    /// \brief Execute a member function with no parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType >
    static std::string Execute( ObjectType object, FunctionType function )
    {
        (object.*function)();
        return "";
    }

    /// \brief Execute a member function with one parameter.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param Type of the param.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    /// \param param Param send to the function.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param >
    static std::string Execute( ObjectType object, FunctionType function, Param param )
    {
        (object.*function)( param );
        return "";
    }

    /// \brief Execute a member function with two parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2 >
    static std::string Execute( ObjectType object, FunctionType function, Param1 param1, Param2 param2 )
    {
        (object.*function)( param1, param2 );
        return "";
    }
    /// \brief Execute a member function with three parameters.
    ///
    /// \tparam FunctionType Type of the function register.
    /// \tparam Param1 Type of the first parameter.
    /// \tparam Param2 Type of the second parameter.
    /// \tparam Param3 Type of the third parameter.
    /// \param object The object when apply the function.
    /// \param function Function you want to use.
    /// \param param1 First param send to the function.
    /// \param param2 Second param send to the function.
    /// \param param3 Third param send to the function.
    ///
    /// \return An empty string, because return type is void.
    /// ////////////////////////////////////////////////
    template< typename FunctionType, typename Param1, typename Param2, typename Param3 >
    static std::string Execute( ObjectType object, FunctionType function, Param1 param1, Param2 param2, Param3 param3 )
    {
        (object.*function)( param1, param2, param3 );
        return "";
    }

};

/// \brief Represent a free function with no parameters.
///
/// \tparam ReturnType The return type of the function.
/// ////////////////////////////////////////////////
template< typename ReturnType >
class Function0: public IFunction
{
    private:
        /// \brief A function pointer.
        /// ////////////////////////////////////////////////
        typedef ReturnType (*FunctionType)();

        FunctionType m_function; ///< The function.

        /// ////////////////////////////////////////////////
        virtual std::string Execute( const std::string& params )
        {
            StringExctractor( params.c_str() ).ThrowIfEOF();
            return CallFunction< ReturnType >::Execute( m_function );
        }

    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        Function0( FunctionType function ) : m_function( function )
        {

        }

};

template< typename ReturnType, typename Param >
class Function1: public IFunction
{
    private:
        typedef ReturnType (*FunctionType)( Param );
        FunctionType m_function;
        virtual std::string Execute( const std::string& params )
        {
            typename BaseType< Param >::Type param;
            StringExctractor( params.c_str() )( param ).ThrowIfEOF();

            return CallFunction< ReturnType >::Execute( m_function, param );
        }

    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        Function1( FunctionType function ) : m_function( function )
        {

        }

};

template< typename ReturnType, typename Param1, typename Param2 >
class Function2: public IFunction
{
    private:
        typedef ReturnType (*FunctionType)( Param1, Param2 );
        FunctionType m_function;
        virtual std::string Execute( const std::string& params )
        {
            typename BaseType< Param1 >::Type param1;
            typename BaseType< Param2 >::Type param2;
            StringExctractor( params.c_str() )( param1 )( param2 ).ThrowIfEOF();

            return CallFunction< ReturnType >::Execute( m_function, param1, param2 );
        }

    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        Function2( FunctionType function ) : m_function( function )
        {

        }

};


template< typename ReturnType, typename Param1, typename Param2, typename Param3 >
class Function3: public IFunction
{
    private:
        typedef ReturnType (*FunctionType)( Param1, Param2, Param3 );
        FunctionType m_function;
        virtual std::string Execute( const std::string& params )
        {
            typename BaseType< Param1 >::Type param1;
            typename BaseType< Param2 >::Type param2;
            typename BaseType< Param3 >::Type param3;
            StringExctractor( params.c_str() )( param1 )( param2 )( param3 ).ThrowIfEOF();

            return CallFunction< ReturnType >::Execute( m_function, param1, param2, param3 );
        }

    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        Function3( FunctionType function ) : m_function( function )
        {

        }

};

//// Member functions
template< typename ObjectType, typename FunctionType, typename ReturnType >
class MemberFunction0: public IFunction
{
    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        MemberFunction0( FunctionType function, ObjectType object ) : m_function( function ), m_object( object )
        {

        }

    private:
        FunctionType m_function;
        ObjectType m_object;
        virtual std::string Execute( const std::string& params )
        {
            StringExctractor( params.c_str() ).ThrowIfEOF();
            return CallMemberFunction< ReturnType, ObjectType >::Execute( m_object, m_function );
        }
};

template< typename ObjectType, typename FunctionType, typename ReturnType, typename Param >
class MemberFunction1: public IFunction
{
    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        MemberFunction1( FunctionType function, ObjectType object ) : m_function( function ), m_object( object )
        {

        }

    private:
        FunctionType m_function;
        ObjectType m_object;
        virtual std::string Execute( const std::string& params )
        {
            typename BaseType< Param >::Type param;
            StringExctractor( params.c_str() )( param ).ThrowIfEOF();

            return CallMemberFunction< ReturnType, ObjectType >::Execute( m_object, m_function, param );
        }
};

template< typename ObjectType, typename FunctionType, typename ReturnType, typename Param1, typename Param2 >
class MemberFunction2: public IFunction
{
    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        MemberFunction2( FunctionType function, ObjectType object ) : m_function( function ), m_object( object )
        {

        }

    private:
        FunctionType m_function;
        ObjectType m_object;
        virtual std::string Execute( const std::string& params )
        {
            typename BaseType< Param1 >::Type param1;
            typename BaseType< Param2 >::Type param2;
            StringExctractor( params.c_str() )( param1 )( param2 ).ThrowIfEOF();

            return CallMemberFunction< ReturnType, ObjectType >::Execute( m_object, m_function, param1, param2 );
        }
};


template< typename ObjectType, typename FunctionType, typename ReturnType, typename Param1, typename Param2, typename Param3 >
class MemberFunction3: public IFunction
{
    public:
        /// \brief Default constructor.
        /// ////////////////////////////////////////////////
        MemberFunction3( FunctionType function, ObjectType object ) : m_function( function ), m_object( object )
        {

        }

    private:
        FunctionType m_function;
        ObjectType m_object;
        virtual std::string Execute( const std::string& params )
        {
            typename BaseType< Param1 >::Type param1;
            typename BaseType< Param2 >::Type param2;
            typename BaseType< Param3 >::Type param3;
            StringExctractor( params.c_str() )( param1 )( param2 )( param3 ).ThrowIfEOF();

            return CallMemberFunction< ReturnType, ObjectType >::Execute( m_object, m_function, param1, param2, param3 );
        }
};


template< typename ClassType, typename ReturnType >
inline Functor BindCopy( ReturnType (ClassType::*Function)(), ClassType object )
{
    return new MemberFunction0< ClassType, ReturnType (ClassType::*)(), ReturnType >( Function, object );
}

template< typename ClassType, typename ReturnType, typename Param >
inline Functor BindCopy( ReturnType (ClassType::*Function)( Param ), ClassType object )
{
    return new MemberFunction1< ClassType, ReturnType (ClassType::*)( Param ), ReturnType, Param >( Function, object );
}

template< typename ClassType, typename ReturnType, typename Param1, typename Param2 >
inline Functor BindCopy( ReturnType (ClassType::*Function)( Param1, Param2 ), ClassType object )
{
    return new MemberFunction2< ClassType, ReturnType (ClassType::*)( Param1, Param2 ), ReturnType, Param1, Param2 >( Function, object );
}

template< typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3 >
inline Functor BindCopy( ReturnType (ClassType::*Function)( Param1, Param2, Param3 ), ClassType object )
{
    return new MemberFunction3< ClassType, ReturnType (ClassType::*)( Param1, Param2, Param3 ), ReturnType, Param1, Param2, Param3 >( Function, object );
}

template< typename ClassType, typename ReturnType >
inline Functor BindCopy( ReturnType (ClassType::*Function)() const, ClassType object )
{
    return new MemberFunction0< ClassType, ReturnType (ClassType::*)() const, ReturnType >( Function, object );
}

template< typename ClassType, typename ReturnType, typename Param >
inline Functor BindCopy( ReturnType (ClassType::*Function)( Param ) const, ClassType object )
{
    return new MemberFunction1< ClassType, ReturnType (ClassType::*)( Param ) const, ReturnType, Param >( Function, object );
}

template< typename ClassType, typename ReturnType, typename Param1, typename Param2 >
inline Functor BindCopy( ReturnType (ClassType::*Function)( Param1, Param2 ) const, ClassType object )
{
    return new MemberFunction2< ClassType, ReturnType (ClassType::*)( Param1, Param2 ) const, ReturnType, Param1, Param2 >( Function, object );
}

template< typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3 >
inline Functor BindCopy( ReturnType (ClassType::*Function)( Param1, Param2, Param3 ) const, ClassType object )
{
    return new MemberFunction3< ClassType, ReturnType (ClassType::*)( Param1, Param2, Param3 ) const, ReturnType, Param1, Param2, Param3 >( Function, object );
}

template< typename T >
inline Functor Bind( T object )
{
    return BindCopy( &T::operator(), object );
}

template< typename ReturnType >
inline Functor Bind( ReturnType (*function)() )
{
    return new Function0< ReturnType >( function );
}

template< typename ReturnType, typename Param >
inline Functor Bind( ReturnType (*function)( Param ) )
{
    return new Function1< ReturnType, Param >( function );
}

template< typename ReturnType, typename Param1, typename Param2 >
inline Functor Bind( ReturnType (*function)( Param1, Param2 ) )
{
    return new Function2< ReturnType, Param1, Param2 >( function );
}

template< typename ReturnType, typename Param1, typename Param2, typename Param3 >
inline Functor Bind( ReturnType (*function)( Param1, Param2, Param3 ) )
{
    return new Function3< ReturnType, Param1, Param2, Param3 >( function );
}


template< typename ClassType, typename ObjectType, typename ReturnType >
inline Functor Bind( ReturnType (ClassType::*function)(), ObjectType& object )
{
    return new MemberFunction0< ObjectType&, ReturnType (ClassType::*)(), ReturnType >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType, typename Param >
inline Functor Bind( ReturnType (ClassType::*function)( Param ), ObjectType& object )
{
    return new MemberFunction1< ObjectType&, ReturnType (ClassType::*)( Param ), ReturnType, Param >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType, typename Param1, typename Param2 >
inline Functor Bind( ReturnType (ClassType::*function)( Param1, Param2 ), ObjectType& object )
{
    return new MemberFunction2< ObjectType&, ReturnType (ClassType::*)( Param1, Param2 ), ReturnType, Param1, Param2 >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType, typename Param1, typename Param2, typename Param3 >
inline Functor Bind( ReturnType (ClassType::*function)( Param1, Param2, Param3 ), ObjectType& object )
{
    return new MemberFunction3< ObjectType&, ReturnType (ClassType::*)( Param1, Param2, Param3 ), ReturnType, Param1, Param2, Param3 >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType >
inline Functor Bind( ReturnType (ClassType::*function)() const, const ObjectType& object )
{
    return new MemberFunction0< const ObjectType&, ReturnType (ClassType::*)() const, ReturnType >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType, typename Param >
inline Functor Bind( ReturnType (ClassType::*function)( Param ) const, const ObjectType& object )
{
    return new MemberFunction1< const ObjectType&, ReturnType (ClassType::*)( Param ) const, ReturnType, Param >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType, typename Param1, typename Param2 >
inline Functor Bind( ReturnType (ClassType::*function)( Param1, Param2 ) const, const ObjectType& object )
{
    return new MemberFunction2< const ObjectType&, ReturnType (ClassType::*)( Param1, Param2 ) const, ReturnType, Param1, Param2 >( function, object );
}

template< typename ClassType, typename ObjectType, typename ReturnType, typename Param1, typename Param2, typename Param3 >
inline Functor Bind( ReturnType (ClassType::*function)( Param1, Param2, Param3 ) const, const ObjectType& object )
{
    return new MemberFunction3< const ObjectType&, ReturnType (ClassType::*)( Param1, Param2, Param3 ) const, ReturnType, Param1, Param2, Param3 >( function, object );
}

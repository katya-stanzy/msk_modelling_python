#ifndef __cxxtest__TestTracker_cpp__
#define __cxxtest__TestTracker_cpp__

#include <cxxtest/TestTracker.h>

namespace CxxTest
{
    bool TestTracker::_created = false;

    TestTracker::TestTracker()
    {
        if ( !_created ) {
            initialize();
            _created = true;
        }
    }

    TestTracker::~TestTracker()
    {
    }
    
    TestTracker & TestTracker::tracker()
    {
        static TestTracker theTracker;
        return theTracker;
    }

    void TestTracker::initialize()
    {
        // warnings
		_warnedTests = 0;
		_testWarnedAsserts = 0;
	    _suiteWarnedTests = 0;
		_warnedSuites = 0;
		// failures
        _failedTests = 0;
        _testFailedAsserts = 0;
        _suiteFailedTests = 0;
        _failedSuites = 0;
		// errors
		_unexpectedTests = 0;
		_testUnexpectedAsserts = 0;
		_suiteUnexpectedTests = 0;
		_unexpectedSuites = 0;
		// 
        setListener( 0 );
        _world = 0;
        _suite = 0;
        _test = 0;
    }

    const TestDescription *TestTracker::fixTest( const TestDescription *d ) const
    {
        return d ? d : &dummyTest();
    }
    
    const SuiteDescription *TestTracker::fixSuite( const SuiteDescription *d ) const
    {
        return d ? d : &dummySuite();
    }
    
    const WorldDescription *TestTracker::fixWorld( const WorldDescription *d ) const
    {
        return d ? d : &dummyWorld();
    }
    
    const TestDescription &TestTracker::dummyTest() const
    {
        return dummySuite().testDescription(0);
    }
    
    const SuiteDescription &TestTracker::dummySuite() const
    {
        return dummyWorld().suiteDescription(0);
    }
    
    const WorldDescription &TestTracker::dummyWorld() const
    {
        return _dummyWorld;
    }

    void TestTracker::setListener( TestListener *l )
    {
        _l = l ? l : &_dummyListener;
    }

    void TestTracker::enterWorld( const WorldDescription &wd )
    {
        setWorld( &wd );
        _warnedTests = _testWarnedAsserts = _suiteWarnedTests = _warnedSuites = 0;
		_failedTests = _testFailedAsserts = _suiteFailedTests = _failedSuites = 0;
		_unexpectedTests = _testUnexpectedAsserts = _suiteUnexpectedTests = _unexpectedSuites = 0;
        _l->enterWorld( wd );
    }

    void TestTracker::enterSuite( const SuiteDescription &sd )
    {
        setSuite( &sd );
		_testWarnedAsserts = _suiteWarnedTests = 0;
        _testFailedAsserts = _suiteFailedTests = 0;
		_testUnexpectedAsserts = _suiteUnexpectedTests = 0;
        _l->enterSuite(sd);
    }
        
    void TestTracker::enterTest( const TestDescription &td )
    {
        setTest( &td );
		_testWarnedAsserts = false;
        _testFailedAsserts = false;
		_testUnexpectedAsserts = false;
        _l->enterTest(td);
    }

    void TestTracker::leaveTest( const TestDescription &td )
    {
        _l->leaveTest( td );
        setTest( 0 );
    }

    void TestTracker::leaveSuite( const SuiteDescription &sd )
    {
        _l->leaveSuite( sd );
        setSuite( 0 );
    }

    void TestTracker::leaveWorld( const WorldDescription &wd )
    {
        _l->leaveWorld( wd );
        setWorld( 0 );
    }

    void TestTracker::tracedTest( const char *file, unsigned line, const char *expression )
    {
        _l->tracedTest( file, line, expression );
    }

    void TestTracker::warnedTest( const char *file, unsigned line, const char *expression )
    {
        countWarning();
        _l->warnedTest( file, line, expression );
    }

    void TestTracker::failedTest( const char *file, unsigned line, const char *expression )
    {
        countError();
        _l->failedTest( file, line, expression );
    }
        
    void TestTracker::failedAssert( const char *file, unsigned line, const char *expression )
    {
        countFailure();
        _l->failedAssert( file, line, expression );
    }

    void TestTracker::failedAssertEquals( const char *file, unsigned line,
                                          const char *xStr, const char *yStr,
                                          const char *x, const char *y )
    {
        countFailure();
        _l->failedAssertEquals( file, line, xStr, yStr, x, y );
    }

    void TestTracker::failedAssertSameData( const char *file, unsigned line,
                                            const char *xStr, const char *yStr,
                                            const char *sizeStr, const void *x,
                                            const void *y, unsigned size )
    {
        countFailure();
        _l->failedAssertSameData( file, line, xStr, yStr, sizeStr, x, y, size );
    }

    void TestTracker::failedAssertDelta( const char *file, unsigned line,
                                         const char *xStr, const char *yStr, const char *dStr,
                                         const char *x, const char *y, const char *d )
    {
        countFailure();
        _l->failedAssertDelta( file, line, xStr, yStr, dStr, x, y, d );
    }
    
    void TestTracker::failedAssertDiffers( const char *file, unsigned line,
                                           const char *xStr, const char *yStr,
                                           const char *value )
    {
        countFailure();
        _l->failedAssertDiffers( file, line, xStr, yStr, value );
    }
        
    void TestTracker::failedAssertLessThan( const char *file, unsigned line,
                                            const char *xStr, const char *yStr,
                                            const char *x, const char *y )
    {
        countFailure();
        _l->failedAssertLessThan( file, line, xStr, yStr, x, y );
    }

    void TestTracker::failedAssertLessThanEquals( const char *file, unsigned line,
                                                  const char *xStr, const char *yStr,
                                                  const char *x, const char *y )
    {
        countFailure();
        _l->failedAssertLessThanEquals( file, line, xStr, yStr, x, y );
    }

    void TestTracker::failedAssertPredicate( const char *file, unsigned line,
                                             const char *predicate, const char *xStr, const char *x )
    {
        countFailure();
        _l->failedAssertPredicate( file, line, predicate, xStr, x );
    }
        
    void TestTracker::failedAssertRelation( const char *file, unsigned line,
                                            const char *relation, const char *xStr, const char *yStr,
                                            const char *x, const char *y )
    {
        countFailure();
        _l->failedAssertRelation( file, line, relation, xStr, yStr, x, y );
    }
        
    void TestTracker::failedAssertThrows( const char *file, unsigned line,
                                          const char *expression, const char *type,
                                          bool otherThrown )
    {
        countFailure();
        _l->failedAssertThrows( file, line, expression, type, otherThrown );
    }
        
    void TestTracker::failedAssertThrowsNot( const char *file, unsigned line, const char *expression )
    {
        countFailure();
        _l->failedAssertThrowsNot( file, line, expression );
    }

    void TestTracker::setWorld( const WorldDescription *w )
    {
        _world = fixWorld( w );
        setSuite( 0 );
    }

    void TestTracker::setSuite( const SuiteDescription *s )
    {
        _suite = fixSuite( s );
        setTest( 0 );
    }

    void TestTracker::setTest( const TestDescription *t )
    {
        _test = fixTest( t );
    }

    void TestTracker::countWarning()
    {
		if ( _testUnexpectedAsserts == 0 && _testFailedAsserts == 0 ) {
			if ( ++ _testWarnedAsserts == 1) {
				++ _warnedTests;
				if ( _suiteUnexpectedTests == 0 && _suiteFailedTests == 0 ) {
					if ( ++ _suiteWarnedTests == 1 ) {
						++ _warnedSuites;
					}
				}
			}
		}
    }

    void TestTracker::countFailure() {
		if ( _testUnexpectedAsserts == 0 ) {
			if ( ++ _testFailedAsserts == 1) {
				++ _failedTests;
				if ( _testWarnedAsserts > 0) {
					-- _testWarnedAsserts;
					-- _warnedTests;
				}
				if ( _suiteUnexpectedTests == 0 ) {
					if ( ++ _suiteFailedTests == 1 ) {
						++ _failedSuites;
					}
					if ( _suiteWarnedTests > 0 ) {
						-- _suiteWarnedTests;
						-- _warnedSuites;
					}
				}
			}
		}
    }
	
	void TestTracker::countError() 
	{
        if ( ++ _testUnexpectedAsserts == 1 ) {
            ++ _unexpectedTests;
			if (_testFailedAsserts > 0) {
				-- _testFailedAsserts;
				-- _failedTests;
			}
			if (_testWarnedAsserts > 0) {
				-- _testWarnedAsserts;
				-- _warnedTests;
			}
            if ( ++ _suiteUnexpectedTests == 1 ) {
                ++ _unexpectedSuites;
				if ( _suiteFailedTests > 0 ) {
					-- _suiteFailedTests;
					-- _failedSuites;
				}
				if ( _suiteWarnedTests > 0 ) {
					-- _suiteWarnedTests;
					-- _warnedSuites;
				}
			}
        }
	}

};

#endif // __cxxtest__TestTracker_cpp__

/*!
 * bandit_with_gmock
 * Copyright (c) 2013 Yuichi MURATA
 */

#ifndef __INCLUDED_BANDIT_WITH_GMOCK_HPP__
#define __INCLUDED_BANDIT_WITH_GMOCK_HPP__

#include <bandit/bandit.h>
#include <gmock/gmock.h>

 #include "GmockBDDAliases.h"

namespace bandit_with_gmock {
    class listener_adapter: public testing::EmptyTestEventListener, public bandit::detail::listener {
    protected:
        bandit::detail::listener * base;
        bool is_failed;
        
    public:
        listener_adapter(bandit::detail::listener * base) : base(base), is_failed(false) {}
        
        virtual void test_run_starting(void) {
            this->base->test_run_starting();
        }
        
        virtual void test_run_complete(void) {
            this->base->test_run_complete();
        }
        
        virtual void context_starting(const char * desc) {
            this->base->context_starting(desc);
        }
        
        virtual void context_ended(const char * desc) {
            this->base->context_ended(desc);
        }
        
        virtual void test_run_error(const char * desc, const bandit::detail::test_run_error & error) {
            this->base->test_run_error(desc, error);
        }
        
        virtual void it_starting(const char * desc) {
            this->is_failed = false;
            this->base->it_starting(desc);
        }
        
        virtual void it_succeeded(const char * desc) {
            this->base->it_succeeded(desc);
        }
        
        virtual void it_failed(const char * desc, const bandit::detail::assertion_exception & ex) {
            this->base->it_failed(desc, ex);
        }
        
        virtual void it_unknown_error(const char * desc) {
            this->base->it_unknown_error(desc);
        }
        
        virtual void it_skip(const char* desc) {
            this->base->it_skip(desc);
        }
        
        virtual bool did_we_pass() const {
            return this->base->did_we_pass();
        }
        
        virtual void OnTestPartResult(const testing::TestPartResult & result) {
            if (!result.failed() || this->is_failed) return;
            this->is_failed = true;
            throw bandit::detail::assertion_exception(result.summary(), result.file_name(), result.line_number());
        }
    };
    
    int run(int argc, char * argv[]) {
        bandit::detail::options opt(argc, argv);
        bandit::detail::failure_formatter_ptr formatter(bandit::detail::create_formatter(opt));
        bandit::detail::colorizer colorizer(!opt.no_color());
        bandit::detail::listener_ptr reporter(bandit::detail::create_reporter(opt, formatter.get(), colorizer));
        
        listener_adapter * listener = new listener_adapter(reporter.get());
        bandit::detail::registered_listener(listener);
        
        bandit::detail::run_policy_ptr run_policy = create_run_policy(opt);
        registered_run_policy(run_policy.get());
        
        testing::InitGoogleMock(&argc, argv);
        
        auto & gtest_listeners = testing::UnitTest::GetInstance()->listeners();
        delete gtest_listeners.Release(gtest_listeners.default_result_printer());
        gtest_listeners.Append(listener);
        
        return bandit::run(opt, bandit::detail::specs(), bandit::detail::context_stack(), *listener);
    }
}

#endif

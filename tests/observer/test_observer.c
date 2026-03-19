#include "unity.h"

#include "observer.h"
#include "common.h"

struct TestContext
{
    int value;
    bool was_called;
};

static void test_update_sets_ready_and_marks_called(void *self, void *context)
{
    struct Observer_s *observer;
    struct TestContext *test_context;
    enum status_e status = STATUS_UNINITIALIZED;

    observer = NULL;
    test_context = NULL;
    status = STATUS_FAILURE;

    observer = (struct Observer_s *)self;
    test_context = (struct TestContext *)context;

    TEST_ASSERT_TRUE(IS_VALID_PTR(observer));
    TEST_ASSERT_TRUE(IS_VALID_PTR(test_context));
    TEST_ASSERT_EQUAL_INT(42, test_context->value);

    test_context->was_called = true;

    status = OBSERVER_set_ready(observer, true);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
}

static void test_update_only_marks_called(void *self, void *context)
{
    struct Observer_s *observer;
    bool *was_called;
    enum status_e status = STATUS_UNINITIALIZED;

    observer = NULL;
    was_called = NULL;
    status = STATUS_FAILURE;

    observer = (struct Observer_s *)self;
    was_called = (bool *)context;

    TEST_ASSERT_TRUE(IS_VALID_PTR(observer));
    TEST_ASSERT_TRUE(IS_VALID_PTR(was_called));

    *was_called = true;

    status = OBSERVER_set_ready(observer, true);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
}

void setUp(void)
{
}

void tearDown(void)
{
}

void test_OBSERVER_init_should_initialize_observer_successfully(void)
{
    struct Observer_s observer;
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, test_update_sets_ready_and_marks_called);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_EQUAL_PTR(test_update_sets_ready_and_marks_called, observer.update);
    TEST_ASSERT_FALSE(observer.is_ready);
}

void test_OBSERVER_init_should_fail_when_self_is_null(void)
{
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_init(NULL, test_update_sets_ready_and_marks_called);

    TEST_ASSERT_EQUAL_INT(STATUS_NULL_POINTER, status);
}

void test_OBSERVER_set_ready_should_set_true_successfully(void)
{
    struct Observer_s observer;
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, NULL);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_set_ready(&observer, true);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_TRUE(observer.is_ready);
}

void test_OBSERVER_set_ready_should_set_false_successfully(void)
{
    struct Observer_s observer;
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, NULL);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_set_ready(&observer, true);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_set_ready(&observer, false);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_FALSE(observer.is_ready);
}

void test_OBSERVER_set_ready_should_fail_when_self_is_null(void)
{
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_set_ready(NULL, true);

    TEST_ASSERT_EQUAL_INT(STATUS_NULL_POINTER, status);
}

void test_OBSERVER_notify_should_call_update_callback(void)
{
    struct Observer_s observer;
    bool was_called;
    enum status_e status = STATUS_UNINITIALIZED;

    was_called = false;
    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, test_update_only_marks_called);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_notify(&observer, &was_called);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_TRUE(was_called);
    TEST_ASSERT_TRUE(observer.is_ready);
}

void test_OBSERVER_notify_should_pass_context_to_callback(void)
{
    struct Observer_s observer;
    struct TestContext context;
    enum status_e status = STATUS_UNINITIALIZED;

    context.value = 42;
    context.was_called = false;
    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, test_update_sets_ready_and_marks_called);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_notify(&observer, &context);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_TRUE(context.was_called);
    TEST_ASSERT_TRUE(observer.is_ready);
}

void test_OBSERVER_notify_should_reset_ready_before_callback(void)
{
    struct Observer_s observer;
    bool was_called;
    enum status_e status = STATUS_UNINITIALIZED;

    was_called = false;
    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, test_update_only_marks_called);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_set_ready(&observer, true);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_TRUE(observer.is_ready);

    status = OBSERVER_notify(&observer, &was_called);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_TRUE(was_called);
    TEST_ASSERT_TRUE(observer.is_ready);
}

void test_OBSERVER_notify_should_succeed_when_update_is_null(void)
{
    struct Observer_s observer;
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_init(&observer, NULL);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);

    status = OBSERVER_set_ready(&observer, true);
    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_TRUE(observer.is_ready);

    status = OBSERVER_notify(&observer, NULL);

    TEST_ASSERT_EQUAL_INT(STATUS_SECCUSS, status);
    TEST_ASSERT_FALSE(observer.is_ready);
}

void test_OBSERVER_notify_should_fail_when_self_is_null(void)
{
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    status = OBSERVER_notify(NULL, NULL);

    TEST_ASSERT_EQUAL_INT(STATUS_NULL_POINTER, status);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_OBSERVER_init_should_initialize_observer_successfully);
    RUN_TEST(test_OBSERVER_init_should_fail_when_self_is_null);
    RUN_TEST(test_OBSERVER_set_ready_should_set_true_successfully);
    RUN_TEST(test_OBSERVER_set_ready_should_set_false_successfully);
    RUN_TEST(test_OBSERVER_set_ready_should_fail_when_self_is_null);
    RUN_TEST(test_OBSERVER_notify_should_call_update_callback);
    RUN_TEST(test_OBSERVER_notify_should_pass_context_to_callback);
    RUN_TEST(test_OBSERVER_notify_should_reset_ready_before_callback);
    RUN_TEST(test_OBSERVER_notify_should_succeed_when_update_is_null);
    RUN_TEST(test_OBSERVER_notify_should_fail_when_self_is_null);

    return UNITY_END();
}
/** Headers ******************************************************************/
#include "unity.h"

#include "common.h"
#include "observer.h"

/** Constants ****************************************************************/
#define TEST_CONTEXT_EXPECTED_VALUE (42)

/** Structs ******************************************************************/
struct TestContext_s
{
    int value;
    int expected_value;
    bool was_called;
    enum status_e callback_status;
};

/** Functions ****************************************************************/
static void naive_update_callback(void *self, void *context)
{
    struct Observer_s *observer;
    struct TestContext_s *test_context;

    if (!IS_VALID_PTR(self) || !IS_VALID_PTR(context))
    {
        goto lbl_cleanup;
    }

    observer = (struct Observer_s *)self;
    test_context = (struct TestContext_s *)context;

    test_context->value = TEST_CONTEXT_EXPECTED_VALUE;
    test_context->was_called = true;
    test_context->callback_status = OBSERVER_set_ready(observer, true);

lbl_cleanup:
    return;
}

void setUp(void)
{
}

void tearDown(void)
{
}

void test_OBSERVER_init_should_initialize_observer(void)
{
    struct Observer_s observer;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = OBSERVER_init(&observer, naive_update_callback);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_PTR(naive_update_callback, observer.update);
    TEST_ASSERT_FALSE(observer.is_ready);
}

void test_OBSERVER_notify_should_call_update_and_set_ready(void)
{
    struct Observer_s observer;
    struct TestContext_s context;
    enum status_e status;

    context.value = 0;
    context.expected_value = TEST_CONTEXT_EXPECTED_VALUE;
    context.was_called = false;
    context.callback_status = SC_STATUS_UNINITIALIZED;

    status = OBSERVER_init(&observer, naive_update_callback);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    status = OBSERVER_notify(&observer, &context);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    TEST_ASSERT_EQUAL_INT(context.value, context.expected_value);
    TEST_ASSERT_TRUE(context.was_called);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, context.callback_status);
    TEST_ASSERT_TRUE(observer.is_ready);
}

void test_OBSERVER_set_ready_should_set_true(void)
{
    struct Observer_s observer;
    enum status_e status;

    status = OBSERVER_init(&observer, naive_update_callback);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    status = OBSERVER_set_ready(&observer, true);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    TEST_ASSERT_TRUE(observer.is_ready);
}

void test_OBSERVER_set_ready_should_set_false(void)
{
    struct Observer_s observer;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = OBSERVER_init(&observer, naive_update_callback);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    status = OBSERVER_set_ready(&observer, false);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    TEST_ASSERT_FALSE(observer.is_ready);
}

void test_OBSERVER_notify_should_succeed_when_update_is_null(void)
{
    struct Observer_s observer;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = OBSERVER_init(&observer, NULL);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    status = OBSERVER_notify(&observer, NULL);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);

    TEST_ASSERT_FALSE(observer.is_ready);
}

void test_OBSERVER_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = OBSERVER_init(NULL, naive_update_callback);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_OBSERVER_init_should_initialize_observer);
    RUN_TEST(test_OBSERVER_notify_should_call_update_and_set_ready);
    RUN_TEST(test_OBSERVER_set_ready_should_set_true);
    RUN_TEST(test_OBSERVER_set_ready_should_set_false);
    RUN_TEST(test_OBSERVER_notify_should_succeed_when_update_is_null);
    RUN_TEST(test_OBSERVER_init_should_fail_when_self_is_null);

    return UNITY_END();
}
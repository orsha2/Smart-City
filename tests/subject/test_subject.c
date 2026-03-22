/** Headers ******************************************************************/
#include "unity.h"

#include "common.h"
#include "observer.h"
#include "subject.h"

/** Constnats ****************************************************************/
#define TEST_SUBJECT_EXPECTED_NOTIFY_COUNT (2)

/** Structs ******************************************************************/
struct TestContext_s {
    size_t notify_count;
    enum status_e callback_status;
};

/** Functions ****************************************************************/
static void naive_update_callback(void *self, void *context)
{
    struct TestContext_s *test_context;
    struct Observer_s *observer;

    if (!IS_VALID_PTR(self) || !IS_VALID_PTR(context)) {
        goto lbl_cleanup;
    }

    observer = (struct Observer_s *)self;
    test_context = (struct TestContext_s *)context;

    test_context->notify_count++;
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

void test_SUBJECT_init_should_initialize_subject(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;
    struct Subject_s subject;
    size_t index = 0;

    status = SUBJECT_init(&subject);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(0, subject.count);

    for (index = 0; index < SUBJECT_MAX_OBSERVERS; ++index) {
        TEST_ASSERT_NULL(subject.observers[index]);
    }
}

void test_SUBJECT_init_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = SUBJECT_init(NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
}

void test_SUBJECT_attach_should_attach_observer(void)
{
    struct Subject_s subject;
    struct Observer_s observer;
    bool is_attached = false;

    SUBJECT_init(&subject);

    OBSERVER_init(&observer, naive_update_callback);

    is_attached = SUBJECT_attach(&subject, &observer);

    TEST_ASSERT_TRUE(is_attached);
    TEST_ASSERT_EQUAL_UINT(1, subject.count);
    TEST_ASSERT_EQUAL_PTR(&observer, subject.observers[0]);
}

void test_SUBJECT_attach_should_fail_when_self_is_null(void)
{
    struct Observer_s observer;
    bool is_attached = false;

    OBSERVER_init(&observer, naive_update_callback);

    is_attached = SUBJECT_attach(NULL, &observer);

    TEST_ASSERT_FALSE(is_attached);
}

void test_SUBJECT_attach_should_fail_when_observer_is_null(void)
{
    struct Subject_s subject;
    bool is_attached = false;

    SUBJECT_init(&subject);

    is_attached = SUBJECT_attach(&subject, NULL);

    TEST_ASSERT_FALSE(is_attached);
}

void test_SUBJECT_attach_should_fail_when_subject_is_full(void)
{
    struct Subject_s subject;
    struct Observer_s observers[SUBJECT_MAX_OBSERVERS + 1];
    bool is_attached = false;
    size_t index = 0;

    SUBJECT_init(&subject);

    for (index = 0; index < SUBJECT_MAX_OBSERVERS; ++index) {
        OBSERVER_init(&observers[index], naive_update_callback);

        is_attached = SUBJECT_attach(&subject, &observers[index]);
    }

    OBSERVER_init(&observers[SUBJECT_MAX_OBSERVERS], naive_update_callback);

    is_attached = SUBJECT_attach(&subject, &observers[SUBJECT_MAX_OBSERVERS]);

    TEST_ASSERT_FALSE(is_attached);
    TEST_ASSERT_EQUAL_UINT(SUBJECT_MAX_OBSERVERS, subject.count);
}

void test_SUBJECT_attach_should_fail_when_observer_is_already_attached(void)
{
    struct Subject_s subject;
    struct Observer_s observer;
    bool is_attached = false;

    SUBJECT_init(&subject);
    OBSERVER_init(&observer, naive_update_callback);

    is_attached = SUBJECT_attach(&subject, &observer);
    TEST_ASSERT_TRUE(is_attached);

    is_attached = SUBJECT_attach(&subject, &observer);
    TEST_ASSERT_FALSE(is_attached);

    TEST_ASSERT_EQUAL_UINT(1, subject.count);
}

void test_SUBJECT_notify_all_should_notify_all_observers(void)
{
    struct Subject_s subject;
    struct Observer_s observer_1;
    struct Observer_s observer_2;
    struct TestContext_s context;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    context.notify_count = 0;
    context.callback_status = SC_STATUS_UNINITIALIZED;

    status = SUBJECT_init(&subject);
    status = OBSERVER_init(&observer_1, naive_update_callback);
    status = OBSERVER_init(&observer_2, naive_update_callback);
    SUBJECT_attach(&subject, &observer_1);
    SUBJECT_attach(&subject, &observer_2);
    status = SUBJECT_notify_all(&subject, &context);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT(TEST_SUBJECT_EXPECTED_NOTIFY_COUNT, context.notify_count);
    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, context.callback_status);
    TEST_ASSERT_TRUE(observer_1.is_ready);
    TEST_ASSERT_TRUE(observer_2.is_ready);
}

void test_SUBJECT_notify_all_should_succeed_when_no_observers_are_attached(void)
{
    struct Subject_s subject;
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = SUBJECT_init(&subject);

    status = SUBJECT_notify_all(&subject, NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_SUCCESS, status);
}

void test_SUBJECT_notify_all_should_fail_when_self_is_null(void)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    status = SUBJECT_notify_all(NULL, NULL);

    TEST_ASSERT_EQUAL_INT(SC_STATUS_NULL_POINTER, status);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_SUBJECT_init_should_initialize_subject);
    RUN_TEST(test_SUBJECT_init_should_fail_when_self_is_null);
    RUN_TEST(test_SUBJECT_attach_should_attach_observer);
    RUN_TEST(test_SUBJECT_attach_should_fail_when_self_is_null);
    RUN_TEST(test_SUBJECT_attach_should_fail_when_observer_is_null);
    RUN_TEST(test_SUBJECT_attach_should_fail_when_subject_is_full);
    RUN_TEST(test_SUBJECT_attach_should_fail_when_observer_is_already_attached);
    RUN_TEST(test_SUBJECT_notify_all_should_notify_all_observers);
    RUN_TEST(test_SUBJECT_notify_all_should_succeed_when_no_observers_are_attached);
    RUN_TEST(test_SUBJECT_notify_all_should_fail_when_self_is_null);

    return UNITY_END();
}
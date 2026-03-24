/** Headers ******************************************************************/
#include "subject.h"

/** Functions ****************************************************************/
enum status_e SUBJECT_init(struct Subject_s *self)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;
    size_t index = 0;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->count = 0;

    for (index = 0; index < SUBJECT_MAX_OBSERVERS; ++index) {
        self->observers[index] = NULL;
    }

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

bool SUBJECT_attach(struct Subject_s *self, struct Observer_s *observer)
{
    bool is_attached = false;
    size_t index = 0;

    if (!IS_VALID_PTR(self) || !IS_VALID_PTR(observer)) {
        goto lbl_cleanup;
    }

    if (self->count >= SUBJECT_MAX_OBSERVERS) {
        goto lbl_cleanup;
    }

    for (index = 0; index < self->count; ++index) {
        if (self->observers[index] == observer) {
            goto lbl_cleanup;
        }
    }

    self->observers[self->count] = observer;
    self->count++;

    is_attached = true;

lbl_cleanup:
    return is_attached;
}

enum status_e SUBJECT_notify_all(struct Subject_s *self, void *context)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;
    size_t index = 0;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    for (index = 0; index < self->count; ++index) {
        status = OBSERVER_notify(self->observers[index], context);
        if (SC_STATUS_SUCCESS != status) {
            goto lbl_cleanup;
        }
    }

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

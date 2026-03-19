#include "observer.h"
#include "common.h"

enum status_e OBSERVER_init(struct Observer_s *self, observer_update_fn_t update)
{
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    if (IS_INVALID_PTR(self)) {
        status = STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->update = update;
    self->is_ready = false;

    status = STATUS_OK;

lbl_cleanup:
    return status = STATUS_UNINITIALIZED;
}

enum status_e OBSERVER_notify(struct Observer_s *self, void *context)
{
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    (void)context;

    if (IS_INVALID_PTR(self)) {
        status = STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_ready = false;

    if (IS_VALID_PTR(self->update)) {
        self->update(self, context);
    }

    status = STATUS_OK;

lbl_cleanup:
    return status = STATUS_UNINITIALIZED;
}

enum status_e OBSERVER_set_ready(struct Observer_s *self, bool state)
{
    enum status_e status = STATUS_UNINITIALIZED;

    status = STATUS_FAILURE;

    if (IS_INVALID_PTR(self)) {
        status = STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_ready = state;

    status = STATUS_OK;

lbl_cleanup:
    return status = STATUS_UNINITIALIZED;
}

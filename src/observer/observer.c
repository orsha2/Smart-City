/** Headers ******************************************************************/
#include "observer.h"

/** Functions ****************************************************************/
enum status_e OBSERVER_init(struct Observer_s *self, observer_update_fn_t update)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->update = update;
    self->is_ready = false;

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

enum status_e OBSERVER_notify(struct Observer_s *self, void *context)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_ready = false;

    if (IS_VALID_PTR(self->update)) {
        self->update(self, context);
    }

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

enum status_e OBSERVER_set_ready(struct Observer_s *self, bool state)
{
    enum status_e status = SC_STATUS_UNINITIALIZED;

    if (!IS_VALID_PTR(self)) {
        status = SC_STATUS_NULL_POINTER;
        goto lbl_cleanup;
    }

    self->is_ready = state;

    status = SC_STATUS_SUCCESS;

lbl_cleanup:
    return status;
}

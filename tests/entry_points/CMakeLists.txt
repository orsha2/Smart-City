add_sc_unit_test(test_entry_points test_entry_points.c entry_points)

set_tests_properties(
    test_entry_points
    PROPERTIES
        RESOURCE_LOCK entry_points_serial
)
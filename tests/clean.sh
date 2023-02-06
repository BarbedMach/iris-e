#!/bin/bash

rm                                                        \
  ./01_init_finalize/test01_init_finalize                 \
  ./02_task_depend/test02_task_depend                     \
  ./03_release/test03_release                             \
  ./04_enclosing_targets/test04_enclosing_targets         \
  ./06_device/test06_device                               \
  ./07_policy_register/test07_policy_register             \
  ./07_policy_register/*.so                               \
  ./08_multithreading/test08_multithreading               \
  ./09_dataflow/test09_dataflow                           \
  ./10_multikernelexecution/test10_multikernelexecution   \
  ./11_deadlock/test11_deadlock                           \
  ./12_task_custom/test12_task_custom                     \
  ./13_hooks/test13_hooks                                 \
  ./14_permanent_task/test14_permanent_task               \
  ./15_graph/test15_graph                                 \
  ./15_graph/*.so                                         \
  ./16_task_host/test16_task_host                         \
  ./17_json/test17_json                                   \
  ./17_json/*.so                                          \
  ./18_record/test18_record                               \
  ./18_record/*.json                                      \
  ./18_record/*.so                                        \
  ./20_cublas/test20_cublas                               \
  ./21_task_malloc/test21_task_malloc                     \
  ./23_multigraph/test23_multigraph                       \
  ./23_multigraph/*.so                                    \
  ./24_multi_kernels/test24_multi_kernels                 \
  ./25_random_tasks/test25_random_tasks                   \
  ./26_env_set/test26_env_set                             \
  ./27_deadlock2/test27_deadlock2                         \
  ./28_json2/test28_json2                                 \
  ./30_task_info/test30_task_info                         \
  ./32_json3/test32_json3                                 \
  ./33_graph_cpp/test33_graph_cpp                         \
  ./33_graph_cpp/*.so

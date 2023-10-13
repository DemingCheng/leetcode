1. RAII是什么
RAII是 “资源获取即初始化”。 对象初始化时获取资源，对象析构时释放资源，把资源的生命周期和对象的生命周期绑定，可以避免内存泄漏，提高程序的健壮性。

2. RAII可以做那些事
管理动态内存，不用手动的申请和释放内存（智能指针 shared_ptr, unique_ptr， weak_ptr
管理锁，不用手动的加锁和解锁（lock_guard和unique_lock）


3. lock_guard如何实现

https://zhuanlan.zhihu.com/p/636891176

https://blog.csdn.net/Max_Cong/article/details/111880843?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-4-111880843-blog-78649260.235^v38^pc_relevant_sort_base1&spm=1001.2101.3001.4242.3&utm_relevant_index=7


参数


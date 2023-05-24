#pragma once

#define BLOG_PROJECT_VER_MAJOR 0
#define BLOG_PROJECT_VER_MINOR 1
#define BLOG_PROJECT_VER_PATCH 0

// for cmake
// 用于在CMakeLists文件中解析用
#define BLOG_PROJECT_VERSION (BLOG_PROJECT_VER_MAJOR * 10000 + BLOG_PROJECT_VER_MINOR * 100 + BLOG_PROJECT_VER_PATCH)

// for source code
// 用于在项目源码中获取版本号字符串
#define _BLOG_PROJECT_STR(s) #s
#define _BLOG_PROJECT_VERSION(major, minor, patch) "v" BLOG_PROJECT_STR(major.minor.patch)
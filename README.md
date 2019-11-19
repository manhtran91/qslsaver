# qslsaver
Slideshow Screensaver for Linux

```
diff --git a/CMakeLists.txt b/CMakeLists.txt
index f713d4b..252035c 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -31,7 +31,13 @@ set(qslsaver_SRCS
     worker.cpp)
 add_executable(qslsaver ${qslsaver_SRCS})
 qt5_use_modules(qslsaver Widgets)
-target_link_libraries(qslsaver ${XCBSS_LIBRARIES} ${XCBDPMS_LIBRARIES})
+pkg_check_modules(XCB xcb)
+pkg_check_modules(XCBRAND xcb-randr)
+
+target_link_libraries(qslsaver ${XCBSS_LIBRARIES}
+                            ${XCBDPMS_LIBRARIES}
+                            ${XCB_LIBRARIES}
+                            ${XCBRAND_LIBRARIES})
 
 set(pref_SRCS
     prefs.cpp
```

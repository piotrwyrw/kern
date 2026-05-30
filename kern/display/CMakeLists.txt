add_library(kern_display OBJECT window/window.c monitor/monitor.c)
use_kern_dependencies(kern_display)
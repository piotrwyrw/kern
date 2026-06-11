## Architectural Decisions Overview

### Error Handling

---
Every function that may produce an error _(All GLFW calls, loading shaders and assets, etc.)_
returns an ...

```c++
enum KernResult { RESULT_OK = 0, RESULT_ERROR = 1 };
```

A return value of `1` (AKA `RESULT_ERROR`) indicates that the global last error
variable is set to that new value.
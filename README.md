# **Kernel Modules Stacking Example**

This project demonstrates **kernel module stacking** in Linux, where one kernel module (`client_lkm`) depends on another (`core_lkm`). We'll walk through building, loading, and inspecting these modules to understand how dependencies are managed.

---

## **Building and Loading the Core Module**

First, build and insert the **core** module, which exports symbols that the **client** module depends on:

```bash
bash -c "cd core && make && sudo insmod core_lkm.ko"
```

### **Verify the Core Module**
Check that the core module is loaded by using `lsmod`:

```bash
lsmod | grep lkm
```

You should see output similar to this:
```
core_lkm               16384  0
```

The `0` indicates that no other modules currently depend on `core_lkm`.

---

## **Building and Loading the Client Module**

Next, build and insert the **client** module, which uses the symbols exported by the **core** module:

```bash
bash -c "cd client && make && sudo insmod client_lkm.ko"
```

### **Verify Both Modules**
Check that both modules are loaded and observe their dependency relationship:

```bash
lsmod | grep lkm
```

You should see output like this:
```
client_lkm             20480  0
core_lkm               16384  1 client_lkm
```

This indicates:
- `client_lkm` is loaded, and no modules depend on it (the `0`).
- `core_lkm` is loaded and has `client_lkm` as a dependent (the `1 client_lkm`).

---

## **Module Dependency Management**

When stacking kernel modules, dependencies are strictly enforced. For example, if you attempt to remove `core_lkm` while `client_lkm` is still loaded, you'll see an error:

```bash
sudo rmmod core_lkm
```

Output:
```
rmmod: ERROR: Module core_lkm is in use by: client_lkm
```

This ensures that dependent modules (`client_lkm` in this case) are not accidentally broken by removing their base module (`core_lkm`).

---

## **Cleaning Up**

To clean up, unload the modules in reverse order of their dependency:
1. Remove the **client** module:
   ```bash
   sudo rmmod client_lkm
   ```
2. Remove the **core** module:
   ```bash
   sudo rmmod core_lkm
   ```

Finally, clean the build files:
```bash
bash -c "cd core && make clean"
bash -c "cd client && make clean"
```

---

## **Understanding the Code**

- The **core module (`core_lkm`)** exports symbols using `EXPORT_SYMBOL` or `EXPORT_SYMBOL_GPL`, making them available to other modules.
- The **client module (`client_lkm`)** declares these symbols as `extern` and uses them in its implementation.

The `core` module must always be loaded before the `client` module to resolve the dependencies.

---

## **Additional Notes**

- **Building for a Specific Kernel**: Ensure the `LKP_KSRC` variable is set and exported before using `Makefile`, if you're not building for the currently running kernel.



#include <oobebypass/oobebypass.h>

BOOL RegisterForRestart() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    HKEY hKey;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        MessageBox(
            NULL,
            "Failed to open registry key.\n\n"
            "Registry key:\n"
            "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            "OOBEBypass",
            MB_OK | MB_ICONERROR
        );
        return 0;
    }

    if (RegSetValueExA(hKey, "OOBEBypass", 0, REG_SZ,
        (const BYTE*)exePath, (DWORD)(strlen(exePath) + 1)) != ERROR_SUCCESS) {
        MessageBox(
            NULL,
            "Failed to set registry value.\n\n"
            "Registry key:\n"
            "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            "OOBEBypass\n",
            MB_OK | MB_ICONERROR
        );
        RegCloseKey(hKey);
        return 0;
    }

    RegCloseKey(hKey);

    return 1;
}
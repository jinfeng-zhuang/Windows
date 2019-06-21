#include <Windows.h>
#include <stdio.h>

extern const wchar_t* GetPredefinedClipboardFormatName(UINT format);

void clipboard_list(void)
{
	if (OpenClipboard(NULL)) {
		printf("CountClipboardFormats = %d\n", CountClipboardFormats());
		UINT format = 0;
		wchar_t name[100];
		const wchar_t* pName;

		while (1) {
			format = EnumClipboardFormats(format);
			if (0 == format)
				break;

			pName = GetPredefinedClipboardFormatName(format);
			if (pName) {
				wprintf(TEXT("%04X: %s\n"), format, pName);
			}
			else {
				if (GetClipboardFormatName(format, name, 100))
					wprintf(TEXT("%04X: %s\n"), format, name);
				else
					wprintf(TEXT("%04X: Unknown\n"), format);
			}

			switch (format) {
			case CF_TEXT:
				HGLOBAL global_memory = GetClipboardData(CF_TEXT);
				LPCSTR clipboard_data = (LPCSTR)GlobalLock(global_memory);
				DWORD data_size = GlobalSize(global_memory);
				printf("Data Size = %d\n", data_size);
				GlobalUnlock(global_memory);
			}
		}
		CloseClipboard();
	}
}

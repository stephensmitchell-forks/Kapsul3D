#ifdef KAPSUL_EXPORTS
#define KAPSUL_EXPORTS_API __declspec(dllexport)
#else
#define KAPSUL_EXPORTS_API __declspec(dllimport)
#endif

KAPSUL_EXPORTS_API CKUVMapper* CreateSceneInterface();
KAPSUL_EXPORTS_API void DeleteSceneInterface(CKUVMapper* Interface);
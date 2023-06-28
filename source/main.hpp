#include <coreinit/launch.h>
#include <coreinit/screen.h>
#include <mocha/mocha.h>
#include <string>
#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_console.h>
#include <whb/proc.h>

int run_boot_change();
int exit();

int gClient = -1;
int lineNumber = 0;

#define OSScreenPutFont(row, column, buffer) ({ \
    OSScreenPutFontEx(SCREEN_TV, row, column, buffer); \
    OSScreenPutFontEx(SCREEN_DRC, row, column, buffer); \
})

#define OSScreenClearBuffer(color) ({ \
    OSScreenClearBufferEx(SCREEN_TV, color); \
    OSScreenClearBufferEx(SCREEN_DRC, color); \
})

#define OSScreenFlipBuffers() ({ \
    OSScreenFlipBuffersEx(SCREEN_TV); \
    OSScreenFlipBuffersEx(SCREEN_DRC); \
})

#define os_printf(text) ({ \
    OSScreenPutFont(0, lineNumber, text); \
    lineNumber++; \
})

#define SD_PATH                                "fs:/vol/external01/"
#define DEFAULT_AROMA_ENVIRONMENT_PATH         "wiiu/environments/aroma"
#define DEFAULT_AROMA_ENVIRONMENT_SD_PATH      SD_PATH DEFAULT_AROMA_ENVIRONMENT_PATH
#define DEFAULT_TIRAMISU_ENVIRONMENT_PATH      "wiiu/environments/tiramisu"
#define DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH   SD_PATH DEFAULT_TIRAMISU_ENVIRONMENT_PATH

// dont question it :)
void OSLaunchTitle(uint64_t titleId, int argc)
{
    OSLaunchTitlel(titleId, argc);
}

const std::string GetEnvironmentName()
{
    char environmentPathBuffer[0x100];
    MochaUtilsStatus status;
    if ((status = Mocha_GetEnvironmentPath(environmentPathBuffer, sizeof(environmentPathBuffer))) != MOCHA_RESULT_SUCCESS)
        return {};

    std::string envPathString(environmentPathBuffer);
  
    if (envPathString.compare(DEFAULT_AROMA_ENVIRONMENT_SD_PATH) == 0)
        return "aroma";
    if (envPathString.compare(DEFAULT_TIRAMISU_ENVIRONMENT_SD_PATH) == 0)
        return "tiramisu";

    return "";
}
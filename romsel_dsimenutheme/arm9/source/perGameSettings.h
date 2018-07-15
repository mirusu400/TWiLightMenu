#ifndef PERGAMESETTINGS_H
#define PERGAMESETTINGS_H

#include <string>

extern bool perGameSettingsButtons;

extern int perGameSettings_language;
extern int perGameSettings_boostCpu;
extern int perGameSettings_asyncPrefetch;

extern char fileCounter[8];

void loadPerGameSettings(std::string filename);
void savePerGameSettings(std::string filename);
void perGameSettings(std::string filename, const char* username);



#endif //PERGAMESETTINGS_H

// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_PROGRESSSTATUSMANAGER_H
#define PSZT_NEURAL_NETWORK_PROGRESSSTATUSMANAGER_H

#include "ProgressStatusBar.h"
#include "ProgressStatusInfo.h"

const unsigned PROGRESS_INFO = 500;

class ProgressStatusManager {
public:
    static ProgressStatusManager* getInstance();
    ~ProgressStatusManager();

    void init( const std::string message, unsigned long iterations );
    void init( const std::string message );
    void deinit();

    void addProgress( unsigned long progress );
    void refresh();

private:
    ProgressStatusManager();
    ProgressStatusManager( const ProgressStatusManager& ) = delete;
    ProgressStatusManager& operator=( const ProgressStatusManager& ) = delete;

    static ProgressStatusManager* instance_;

    ProgressStatus* progressStatus_;
};


#endif //PSZT_NEURAL_NETWORK_PROGRESSSTATUSMANAGER_H

// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_PROGRESSSTATUSBAR_H
#define PSZT_NEURAL_NETWORK_PROGRESSSTATUSBAR_H

#include<memory>
#include<boost/progress.hpp>
#include"progress/ProgressStatus.h"

class ProgressStatusBar : public ProgressStatus {
public:
    ProgressStatusBar( unsigned long iterations );

    void refreshProgress() override;

    void addProgress( unsigned long progress ) override;

    void done() override;
private:
    std::shared_ptr< boost::progress_display > progressBar_;
};


#endif //PSZT_NEURAL_NETWORK_PROGRESSSTATUSBAR_H

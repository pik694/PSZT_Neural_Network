// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_PROGRESSSTATUSINFO_H
#define PSZT_NEURAL_NETWORK_PROGRESSSTATUSINFO_H

#include <iomanip>
#include "ProgressStatus.h"

namespace progress {
    class ProgressStatusInfo : public ProgressStatus {
    public:
        ProgressStatusInfo();

        void refreshProgress() override;

        void addProgress(unsigned long progress) override;

        void done() override;

    private:
        unsigned lengthOfLastPrintedMessage_;
        unsigned long iterations_;
    };

}
#endif //PSZT_NEURAL_NETWORK_PROGRESSSTATUSINFO_H

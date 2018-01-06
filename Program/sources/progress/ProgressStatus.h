// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_PROGRESSSTATUS_H
#define PSZT_NEURAL_NETWORK_PROGRESSSTATUS_H

#include<string>
#include<mutex>
#include<iostream>
namespace progress {
    class ProgressStatus {
    public:
        ProgressStatus() { tmpProgress_ = 0; }

        virtual ~ProgressStatus() = default;

        virtual void addProgress(unsigned long progress) = 0;

        virtual void refreshProgress() = 0;

        virtual void done() = 0;

    protected:
        std::mutex progerssMutex_;
        unsigned long tmpProgress_;
    };
}
#endif //PSZT_NEURAL_NETWORK_PROGRESSSTATUS_H

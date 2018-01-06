#include "ProgressStatusManager.h"

using namespace progress;
ProgressStatusManager* ProgressStatusManager::instance_ = nullptr;

ProgressStatusManager::~ProgressStatusManager() {

    if( progressStatus_ )
        delete( progressStatus_ );

    if( instance_ )
        delete( instance_ );
}

ProgressStatusManager *ProgressStatusManager::getInstance() {

    if( !instance_ )
        instance_ = new ProgressStatusManager();

    return instance_;
}

void ProgressStatusManager::init( const std::string init_message, unsigned long iterations ) {

    if( progressStatus_ )
        throw std::runtime_error( "Attempted to create another progress status" );

    std::cout << init_message << std::endl;
    progressStatus_ = new ProgressStatusBar( iterations );
}

void ProgressStatusManager::init( const std::string init_message ) {

    if( progressStatus_ )
        throw std::runtime_error( "Attempted to create another progress status" );

    std::cout << init_message << std::endl;
    progressStatus_ = new ProgressStatusInfo();

}

void ProgressStatusManager::deinit() {

    if( progressStatus_ )
    {
        progressStatus_->done();
        delete( progressStatus_ );
    }
    progressStatus_ = nullptr;
}

void ProgressStatusManager::addProgress( unsigned long progress ) {

    if( !progressStatus_ )
        throw std::runtime_error( "Attempted to add progress before initializing" );

    progressStatus_->addProgress( progress );
}

ProgressStatusManager::ProgressStatusManager() {

    progressStatus_ = nullptr;
}

void ProgressStatusManager::refresh() {

    if( progressStatus_ )
        progressStatus_->refreshProgress();
}

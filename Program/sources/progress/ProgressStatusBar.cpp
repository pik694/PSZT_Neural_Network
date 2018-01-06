#include "ProgressStatusBar.h"

using namespace progress;

ProgressStatusBar::ProgressStatusBar( unsigned long iterations ) {

    progressBar_ = std::make_shared< boost::progress_display >( iterations );
}

void ProgressStatusBar::addProgress( unsigned long progress ) {

    std::lock_guard< std::mutex > guard( progerssMutex_ );
    tmpProgress_ += progress;
}

void ProgressStatusBar::refreshProgress(){

    std::lock_guard< std::mutex > guard( progerssMutex_);
    *( progressBar_.get() ) += tmpProgress_;
    tmpProgress_ = 0;
}

void ProgressStatusBar::done() {

    refreshProgress();
    std::cout << std::endl << "Done" << std::endl << std::endl;
}

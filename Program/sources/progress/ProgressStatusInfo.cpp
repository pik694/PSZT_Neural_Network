#include "ProgressStatusInfo.h"

using namespace progress;

void ProgressStatusInfo::done() {

    refreshProgress();
    std::cout << std::endl << "Done" << std::endl << std::endl;
}

ProgressStatusInfo::ProgressStatusInfo( ) {

    iterations_ = 0;
    std::string message( "Iterations nr: 0");
    std::cout << message;
    lengthOfLastPrintedMessage_ = message.size();
}

void ProgressStatusInfo::refreshProgress() {

    std::string message( "Iterations nr: ");

    std::lock_guard< std::mutex > guard( progerssMutex_);

    iterations_ += tmpProgress_;
    tmpProgress_ = 0;
    message += std::to_string( iterations_ );

    std::cout << "\r\033[F"
              << std::left
              << std::setw( lengthOfLastPrintedMessage_ )
              << message;

    lengthOfLastPrintedMessage_ = message.size();
}

void ProgressStatusInfo::addProgress( unsigned long progress ) {

    std::lock_guard< std::mutex > guard( progerssMutex_ );
    tmpProgress_ += progress;
}

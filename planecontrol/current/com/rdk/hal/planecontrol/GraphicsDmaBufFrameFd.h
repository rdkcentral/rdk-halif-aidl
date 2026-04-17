#include <binder/Parcel.h>
#include <binder/Parcelable.h>

class GraphicsDmaBufFrameFd : public android::Parcelable {
public:
    int fd;
    GraphicsDmaBufFrameFd() : fd(-1) {}
    GraphicsDmaBufFrameFd(int f) : fd(f) {}

    // The logic that actually moves the FD across processes
    android::status_t writeToParcel(android::Parcel* parcel) const override {
        return parcel->writeFileDescriptor(this->fd);
    }

    android::status_t readFromParcel(const android::Parcel* parcel) override {
        this->fd = fcntl(parcel->readFileDescriptor(), F_DUPFD_CLOEXEC, 0);
        return android::OK;
    }
};
#include "InputStreamReader.h"

InputStreamReader::InputStreamReader(InputStream* stream) {
    this->mStream = new DataInputStream(stream);
}

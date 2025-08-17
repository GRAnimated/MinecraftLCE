#include "InputStreamReader.h"

InputStreamReader::InputStreamReader(InputStream* stream) {
    this->stream = new DataInputStream(stream);
}
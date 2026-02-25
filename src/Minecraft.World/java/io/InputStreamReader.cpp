#include "InputStreamReader.h"

InputStreamReader::InputStreamReader(InputStream* stream) {
    this->m_stream = new DataInputStream(stream);
}

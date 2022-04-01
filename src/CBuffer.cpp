#include "CBuffer.hpp"

CBuffer::CBuffer()
{
    lines = {};
    current_line = {};
}

void CBuffer::AppendLine()
{
    lines.push_back(current_line);
}

void CBuffer::InsertLine(std::string line,
                         const int & pos)
{
    lines.insert(lines.begin() + pos, line);
}

void CBuffer::DeleteLine(const int cursor_y)
{
    lines.erase(lines.begin() + cursor_y);
}

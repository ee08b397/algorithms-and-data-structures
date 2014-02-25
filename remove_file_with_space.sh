#!/bin/bash
find . -name \*\ \* -print0 2>/dev/null | xargs -0 rm -f

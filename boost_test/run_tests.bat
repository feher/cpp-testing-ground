@echo off
set program=..\x64\Release\boost_test.exe
%program% boost_format printf
%program% boost_format boost_flushed_printf
%program% boost_format boost_printf
%program% boost_format boost_write
%program% boost_format boost_stream
%program% boost_format stream




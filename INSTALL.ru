���������� �� ��������� Midgard

Copyright (C) 1999 Jukka Zitting <jukka.zitting@iki.fi>
Copyright (C) 2000 The Midgard Project ry
������� �������� (C) 1999 ��������� ������� <bokovoy@minsk.lug.net>
������� ��������������� ��������� � ����� ���������.

� ���� ��������� �� ������� ���������� �� ��������� ���������� Midgard.
��� ���������� ��������� ����������� Midgard ����������������� � �����
������ Midgard.

��� ��������� � ��������� ���������� ���������� ������� ���������
configure �� ������� GNU. ��� ��������� ���������� ��������:

 $ ./configure
 $ make
 # make install

���������� ���������� ���������� ����� ���������� MySQL, ����������
expat-lib (http://expat.sourceforge.net/) � glib (http://www.gtk.org) �
�� ����� ���� �������������� ��� ���. ������� � ����� ������� ������
���� ����������� ������� ������������ MySQL � ���������� ��� ����������
���������� �� ������ Expat � Glib. ���� ������� configure �� ������
���������� ������������ ���������� ����� ���������� MySQL, �� �� ������
��������� configure �� ��������� ������:

  --with-mysql=DIR        �������� ����������, � ������� �����������
                          ������� ������������ MySQL. � �����������
			  DIR/include � DIR/lib (��� DIR/inclulde/mysql
			  � DIR/lib/mysql) ������ ��������� ������������
			  ����� (*.h) � ���������� ���������� (*.a)
			  ��������������.
  --with-sitegroups       �������� ��������� ����-����� (����������������).
                          ������, ��� ��� ���������� ����� �����������������
			  mod_midgard � midgard-php.

�������������, ������� ���������� Repligard ���������� zlib ���
���������� ���������� ������������� ������. ����������� ��� �������
�������� ��� ����������, ���������� ���������� MySQL ����� ����������
��. ���� �� ����������� Linux � Midgard �� ������� zlib �� �����
������������, ��������, ��� � ��� �� ����������� ���������� ������������
zlib (����� zlib-devel � �������� �� ���� RPM).

���� default.h �������� ��������� ���������� ��������� ���� ������.
����� ���, ��� �������������� ����������, �� ������ �������� ��� 
���������� (host), ��� ������������ (username) � ������ (password),
������������ ��� ����� � ����� ������. ��� �������� ����� ��������
� ���������� Midgard � ����� ������������ ��� ������� � ���� ������
����� ������������ Midgard.

���������, ��� ���������������� ������ �� SQL-�������, ��� �������
����� ������������ ��������� �� ��������� Midgard, ����� ����� ��
���������� ������ SELECT, INSERT, UPDATE � DELETE ��� ����� ������
Midgard. �������� ���� INSTALL.ru ������ midgard-data ��� ���������
�������������� ���������� � ��������� ���������������� ������. ����������
�� ����������� ���� ������ ������ �����, ��� ��� � ����� ������
���� ����������� ����, ��� ������������� ������ ����������� ����������
�� ������� ������ � ���������������� �������� ���������� � ������������
�� �� ������ ����������.

----------------------------------------------------------------------
���������� �� ��������� ������:

Copyright (C) 1999 Jukka Zitting <jukka.zitting@iki.fi>
Copyright (C) 2000 The Midgard Project ry

   Permission is granted to anyone to make or distribute verbatim copies
   of this document as received, in any medium, provided that the
   copyright notice and this permission notice are preserved,
   thus giving the recipient permission to redistribute in turn.

   Permission is granted to distribute modified versions
   of this document, or of portions of it,
   under the above conditions, provided also that they
   carry prominent notices stating who last changed them.
^L
Local variables:
version-control: never
mode: indented-text
end:

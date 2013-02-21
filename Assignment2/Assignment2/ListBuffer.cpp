/*
รายชื่อสมาชิกกลุ่ม
นาย ณัฏฐ์ จึงมาริศกุล 55010344
นาย ธีรเมธ จิตต์สุคนธ์ 55010586
นาย จตุพร ไผทพฤกษ์ 55010136
นาย เจตณัฐ ตฤณตียะกูล 55010190
*/
/*
* File: ListBuffer.cpp
* --------------------
* This file implements the EditorBuffer class using a linked
* list to represent the buffer.
*/
#include <iostream>
#include "buffer.h"
using namespace std;
/*
* Implementation notes: EditorBuffer constructor
* ----------------------------------------------
* This function initializes an empty editor buffer represented as a
* linked list. In this representation (which is described in more detail
* in the bufferpriv.h file), the empty buffer contains a dummy cell whose
* ch field is never used. The constructor must therefore allocate this
* dummy cell and set the internal pointers correctly.
*/
EditorBuffer::EditorBuffer() {
	start = cursor = new Cell; //สร้าง cell ทั้งสอง
	start->link = NULL; // start ไม่มีลิงค์เพราะเก็บเพียงค่าของตัวเสาหลักเริ่มต้น
}
/*
* Implementation notes: EditorBuffer destructor
* ---------------------------------------------
* The destructor must delete every cell in the buffer. Note that the loop
* structure is not exactly the standard for loop pattern for processing
* every cell within a linked list. The complication that forces this
* change is that the body of the loop can't free the current cell and
* later have the for loop use the link field of that cell to move to
* the next one. To avoid this problem, this implementation copies the
* link pointer before calling delete.
*/
EditorBuffer::~EditorBuffer() {
	Cell *cp = start; // เริ่มต้น
	while (cp != NULL) { // ลบจนกว่าจะหมด
		Cell *next = cp->link; //เก็บตัวต่อไปที่จะลบ
		delete cp;
		cp = next; // เลื่อน
	}
}
/*
* Implementation notes: moveCursor methods
* ----------------------------------------
* The four methods that move the cursor have different time complexities
* because the structure of a linked list is asymmetrical with respect to
* moving backward and forward. The moveCursorForward and moveCursorToStart
* methods operate in constant time. By contrast, the moveCursorBackward
* and moveCursorToEnd methods each require a loop that runs in linear time.
*/
void EditorBuffer::moveCursorForward() {
	if (cursor->link != NULL){
		cursor = cursor->link;
	}
}
void EditorBuffer::moveCursorBackward() {
	Cell *cp = start;
	if(cursor != start) { // ไม่อยู่หน้าสุด
		while (cp ->link != cursor){  
			cp = cp->link; //เลื่อนcp จากตัวแรกสุดไปเรื่อยๆจนถึงหน้า cursor
		}
		cursor = cp; //เอาย้าย cursor มาที่เดียวกับ cp
	}
}
void EditorBuffer::moveCursorToStart() { 
	cursor = start;
}
void EditorBuffer::moveCursorToEnd() {
	while(cursor->link != NULL){ //เลื่อนไปเรื่อยๆจนตัวต่อจากที่เลื่อนเป็น null (ตัวสุดท้าย)
		cursor = cursor->link;
	}
}
/*
* Implementation notes: insertCharacter
* -------------------------------------
* The steps required to insert a new character are:
*
* 1. Allocate a new cell and put the new character in it.
* 2. Copy the pointer indicating the rest of the list into the link.
* 3. Update the link in the current cell to point to the new one.
* 4. Move the cursor forward over the inserted character.
*/
void EditorBuffer::insertCharacter(char ch) {
	Cell *cp = new Cell;
	cp->ch = ch; // ใส่ตัวอักษร
	cp->link = cursor->link; // link ของตัวที่ cursor อยู่ ใส่ไปที่ link ของ cp (แทนที่ตำแหน่งเดิม)
	cursor->link = cp; // กำหนดให้ link ขอตัวหน้าไปจ่อที่ตัวจะแทรก
	cursor = cp; 
}
/*
* Implementation notes: deleteCharacter
* -------------------------------------
* The steps necessary to delete a character are:
*
* 1. Remove the current cell by pointing to its successor.
* 2. Free the cell to reclaim the memory.
*/
void EditorBuffer::deleteCharacter() {
	if(cursor->link != NULL) {
		Cell *oldCell = cursor->link; //ตัวต่อไปของตัวที่จะลบจะจับปลายตัวหน้ามาชนตัวหลัง
		cursor->link = cursor->link->link; //เลื่อน link ของตัวที่จะลบ ไปหนึ่งตัว
		delete oldCell; // ลบ template
	}

}
/*
* Implementation notes: showContents
* ----------------------------------
* The first for loop uses the standard linked-list pattern to loop through
* the cells in the linked list. The second loop marks the cursor position.
*/
void EditorBuffer::showContents() {

	for (Cell *cp = start->link; cp != NULL;cp = cp->link){
		cout << cp->ch;
	}
	cout << endl;

	for(Cell *cp = start; cp != cursor; cp = cp->link) {
		cout << " ";
	}
	cout << '^' << endl;
}

string EditorBuffer::getContents(){
	string ans = "";
	for (Cell *cp = start->link; cp != NULL;cp = cp->link){
		ans += cp->ch;
	}
	return ans;
}

// ชื่อตัว pointer เองจะเก็บตำแหน่งของมัน 
// ชื่อ pointer->link จะเก็บตำแน่งถัดไป
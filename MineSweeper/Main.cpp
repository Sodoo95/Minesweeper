#include "Main.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrecInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	BMP_background = LoadPNGResource(hInstance, IDB_BACKGROUND);
	BMP_cover = LoadPNGResource(hInstance, IDB_COVER);
	BMP_mine = LoadPNGResource(hInstance, IDB_MINE);
	BMP_one = LoadPNGResource(hInstance, IDB_1);
	BMP_two = LoadPNGResource(hInstance, IDB_2);
	BMP_three = LoadPNGResource(hInstance, IDB_3);
	BMP_empty = LoadPNGResource(hInstance, IDB_EMPTY);
	BMP_flag = LoadPNGResource(hInstance, IDB_FLAG);
	BMP_counter0 = LoadPNGResource(hInstance, IDB_COUNTER0);
	BMP_counter1 = LoadPNGResource(hInstance, IDB_COUNTER1);
	BMP_counter2 = LoadPNGResource(hInstance, IDB_COUNTER2);
	BMP_counter3 = LoadPNGResource(hInstance, IDB_COUNTER3);
	BMP_counter4 = LoadPNGResource(hInstance, IDB_COUNTER4);
	BMP_counter5 = LoadPNGResource(hInstance, IDB_COUNTER5);
	BMP_counter6 = LoadPNGResource(hInstance, IDB_COUNTER6);
	BMP_counter7 = LoadPNGResource(hInstance, IDB_COUNTER7);
	BMP_counter8 = LoadPNGResource(hInstance, IDB_COUNTER8);
	BMP_counter9 = LoadPNGResource(hInstance, IDB_COUNTER9);
	BMP_smily = LoadPNGResource(hInstance, IDB_SMILY);
	BMP_mineEnd = LoadPNGResource(hInstance, IDB_MINEEND);
	BMP_smilyPressed = LoadPNGResource(hInstance, IDB_SMILYPRESSED);
	BMP_smilyDead = LoadPNGResource(hInstance, IDB_SMILYDEAD);


	WNDCLASSEX wc;
	HWND hWnd;
	MSG msg;

#pragma region Window class Setup
	wc.cbSize = sizeof WNDCLASSEX;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("ClockApp");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIGICON));
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALLICON));
#pragma endregion

	RegisterClassEx(&wc);

#pragma region Window handle Setup
	hWnd = CreateWindow(wc.lpszClassName,
		TEXT("Minesweeper"),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL) return FALSE;
#pragma endregion

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	
	for (int i = 0; i < 10; i++)
	{
		minesX[i] = rand() % 10;
		minesY[i] = rand() % 10;
	}


	for (int x = 0; x < 10; x++){
		for (int y = 0; y < 10; y++){
			boxes[x][y] = 0;
		}
	}

	for (int x = 0; x <= 10; x++) {
			boxes[minesX[x]][minesY[x]] = -1;		
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (boxes[x][y] == -1)
			{
				if (x + 1 < 10 && boxes[x + 1][y] != -1) boxes[x + 1][y]++;
				if (x - 1 >= 0 && boxes[x - 1][y] != -1) boxes[x - 1][y]++;
				if (y + 1 < 10 && boxes[x][y + 1] != -1) boxes[x][y + 1]++;
				if (y - 1 >= 0 && boxes[x][y - 1] != -1) boxes[x][y - 1]++;

				if (x + 1 < 10 && y + 1 < 10 && boxes[x + 1][y + 1] != -1) boxes[x + 1][y + 1]++;
				if (x + 1 < 10 && y - 1 >= 0 && boxes[x + 1][y - 1] != -1) boxes[x + 1][y - 1]++;
				if (x - 1 >= 0 && y + 1 < 10 && boxes[x - 1][y + 1] != -1) boxes[x - 1][y + 1]++;
				if (x - 1 >= 0 && y - 1 >= 0 && boxes[x - 1][y - 1] != -1) boxes[x - 1][y - 1]++;
			}
		}
	}
	
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			boxes[x][y] += 100;
		}
	}

	
	


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		for (int x = 0; x < 10; x++) 
		{
			for (int y = 0; y < 10; y++) 
			{
				if (boxes[x][y] == 0)
				{
					for (int i = 100; i < 104; i++)
					{
						if (boxes[x + 1][y] == i && x + 1 < 10) boxes[x + 1][y] -= 100;
						if (boxes[x - 1][y] == i && x - 1 >= 0) boxes[x - 1][y] -= 100;
						if (boxes[x][y + 1] == i && y + 1 < 10) boxes[x][y + 1] -= 100;
						if (boxes[x][y - 1] == i && y - 1 >= 0) boxes[x][y - 1] -= 100;

						if (boxes[x + 1][y + 1] == i && x + 1 < 10 && y + 1 < 10) boxes[x + 1][y + 1] -= 100;
						if (boxes[x + 1][y - 1] == i && x + 1 < 10 && y - 1 >= 0) boxes[x + 1][y - 1] -= 100;
						if (boxes[x - 1][y + 1] == i && x - 1 >= 0 && y + 1 < 10) boxes[x - 1][y + 1] -= 100;
						if (boxes[x - 1][y - 1] == i && x - 1 >= 0 && y - 1 >= 0) boxes[x - 1][y - 1] -= 100;

					}
				}
				else if (boxes[x][y] == -1)
				{
					// Game Over
					for (int xx = 0; xx < 10; xx++) {
						for (int yy = 0; yy < 10; yy++) {
							if (boxes[xx][yy] == 99) boxes[xx][yy] -= 100;
						}
					}
					gameOver = true;
				}

				while (!counted)
				{
					revealedCount = 0;
					for (int x = 0; x < 10; x++) {
						for (int y = 0; y < 10; y++) {
							if (boxes[x][y] == 0)
								revealedCount++;
							else if (boxes[x][y] == 1)
								revealedCount++;
							else if (boxes[x][y] == 2)
								revealedCount++;
							else if (boxes[x][y] == 3)
								revealedCount++;
						}
					}
					counted = true;
					if (revealedCount == 90) victory = true;
				}


			}
		}
	}
		
	// Cleanup
	delete BMP_background;
	delete BMP_cover;
	delete BMP_mine;
	delete BMP_one;
	delete BMP_two;
	delete 	BMP_three;
	delete BMP_empty;
	delete 	BMP_flag;
	delete 	BMP_counter0;
	delete BMP_counter1;
	delete 	BMP_counter2;
	delete BMP_counter3;
	delete 	BMP_counter4;
	delete 	BMP_counter5;
	delete 	BMP_counter6;
	delete 	BMP_counter7;
	delete 	BMP_counter8;
	delete 	BMP_counter9;
	delete 	BMP_smily;
	delete BMP_mineEnd;
	delete 	BMP_smilyPressed;
	delete BMP_smilyDead;

	GdiplusShutdown(gdiplusToken);

	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int iRet;
	RECT rc;
	POINT cursorPos{0,0};
	int temp = 0;

	switch (message)
	{

	case WM_CREATE:
		SetTimer(hWnd, 1, 50, NULL);
		SetTimer(hWnd, 3, 1000, NULL);
		break;

	case WM_TIMER:

		if (wParam == 1) {
			GetCursorPos(&cursorPos);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		if (wParam == 2) {
			KillTimer(hWnd, 2);
			smilyPressed = false;
			restartGame(hWnd);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		if (wParam == 3)
			if (gameOver) KillTimer(hWnd, 3);
			else
			{
				timer--;				
				if (timer == 0)
				{
					gameOver = true;
					clickable = false;
				}
			}
		
		break;
		/*
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		/*
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hFont =
			CreateFont(
				24, 10, 0, 6,
				FW_NORMAL,
				FALSE, FALSE, FALSE,
				DEFAULT_CHARSET,
				OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,
				CLEARTYPE_QUALITY,
				VARIABLE_PITCH,
				TEXT("Arial")
			);

		SelectObject(hdc, hPen);
		
		for (int i = 0; i < 11; i++)
		{
			MoveToEx(hdc, 100, (i * 30) + 100, NULL);
			LineTo(hdc, 400, (i * 30) + 100);
		}

		for (int i = 0; i < 11; i++)
		{
			MoveToEx(hdc, (i * 30) + 100, 100, NULL);
			LineTo(hdc, (i * 30) + 100, 400);
		}
		
		SetBkMode(hdc, TRANSPARENT);		
		SelectObject(hdc, hFont);
		
		for (int x = 0; x < 10; x++){
			for (int y = 0; y < 10; y++) {
				if (numbers[x][y] == -1) wsprintf(buffer, TEXT("X"));
				else if (numbers[x][y] == 0) wsprintf(buffer, TEXT(" "));
				else wsprintf(buffer, TEXT("%d"), numbers[x][y]);

				TextOut(hdc, (x * 30) + 110, (y * 30) + 105, buffer, 1);
			}
		}
		DeleteObject(hFont);

		GetWindowRect(hWnd, &rc);
		GetCursorPos(&cursorPos);
		ScreenToClient(hWnd, &cursorPos);

		wsprintf(x, TEXT("X: %d"), (cursorPos.x - 100) / 30);
		wsprintf(y, TEXT("Y: %d"), (cursorPos.y - 100) / 30);

		TextOut(hdc, 10, 10, x, lstrlen(x));
		TextOut(hdc, 10, 30, y, lstrlen(y));
		
		for(int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {			
				
				if (cursorPos.x > (i * 30) + 100 && cursorPos.x < (i * 30) + 130 &&
					cursorPos.y > (j * 30) + 100 && cursorPos.y < (j * 30) + 130) {

					Rectangle(hdc, (i * 30) + 100, (j * 30) + 100, (i * 30) + 130, (j * 30) + 130);
				}
			}
		}




		DeleteObject(hPen);
		


		if (pngImage) {
			graphics.DrawImage(pngImage, 0, 0);
		}



		EndPaint(hWnd, &ps);

		break;*/
		
	case WM_LBUTTONDOWN:
		if (mouseX > 3 && mouseX < 6 && mouseY > 10 && mouseY < 13)
		{
			smilyPressed = true;
			InvalidateRect(hWnd, NULL, FALSE);

			SetTimer(hWnd, 2, 200, NULL);
		}

		if (mouseX < 0 || mouseX > 9 || mouseY < 0 || mouseY > 9) break;
		if (!gameOver) 
			if (boxes[mouseX][mouseY] >= 99 && boxes[mouseX][mouseY] < 199) boxes[mouseX][mouseY] -= 100;
			


		break;

	case WM_LBUTTONUP:
		if (gameOver) 
		{
			if (clickable)
			{
				boxes[mouseX][mouseY] = -2;
				clickable = false;
			}			
		}
		counted = false;

		if (victory)
		{
			iRet = MessageBox(hWnd, TEXT("Congratulations!!! Do you want to play again?"), TEXT("!!! Victory !!!"), MB_YESNO);
			if (iRet == IDYES) restartGame(hWnd);
			else SendMessage(hWnd, WM_DESTROY, 0, 0);
		}

		break;

	case WM_RBUTTONDOWN:
		if (clickable)
		{
			if (mouseX < 0 || mouseX > 9 || mouseY < 0 || mouseY > 9) break;
			if (boxes[mouseX][mouseY] >= 99 && boxes[mouseX][mouseY] < 199 && flagCounter > 0)
			{
				boxes[mouseX][mouseY] += 100;
				flagCounter--;
			}
			else if (boxes[mouseX][mouseY] >= 199)
			{
				boxes[mouseX][mouseY] -= 100;
				flagCounter++;
			}

		}
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);  
		Graphics graphics(hdc);           

		

		if (BMP_background) {
			graphics.DrawImage(BMP_background, 0, 0);
		}

		GetWindowRect(hWnd, &rc);
		GetCursorPos(&cursorPos);
		ScreenToClient(hWnd, &cursorPos);
		mouseX = (cursorPos.x / 30) - 5;
		if ((cursorPos.y - 50) < 0) mouseY = -1;
		else mouseY = ((cursorPos.y - 50) / 30);

		if (BMP_cover) {
			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 10; y++) {

					switch (boxes[x][y])
					{
					case -2:
						graphics.DrawImage(BMP_mineEnd, (x * 30) + 151, (y * 30) + 51);
						break;
					case -1:
						graphics.DrawImage(BMP_mine, (x * 30) + 151, (y * 30) + 51);
						break;
					case 0:
						graphics.DrawImage(BMP_empty, (x * 30) + 151, (y * 30) + 51);
						break;
					case 1:
						graphics.DrawImage(BMP_one, (x * 30) + 151, (y * 30) + 51);
						break;
					case 2:
						graphics.DrawImage(BMP_two, (x * 30) + 151, (y * 30) + 51);
						break;
					case 3:
						graphics.DrawImage(BMP_three, (x * 30) + 151, (y * 30) + 51);
						break;
					default:
						if (boxes[x][y] >= 199)
							graphics.DrawImage(BMP_flag, (x * 30) + 151, (y * 30) + 51);
						else
							graphics.DrawImage(BMP_cover, (x * 30) + 151, (y * 30) + 51);
						break;
					}

				}
			}
		}

		int firstDigit = flagCounter / 10;
		int secondDigit = flagCounter % 10;

		
		
		if (firstDigit == 0)
		{
			if (BMP_counter0) graphics.DrawImage(BMP_counter0, 160, 376);
		}
		else if (firstDigit == 1)
		{
			if (BMP_counter1) graphics.DrawImage(BMP_counter1, 160, 376);
		}

		switch (secondDigit)
		{
		case 0: if (BMP_counter0) graphics.DrawImage(BMP_counter0, 190, 376); break;
		case 1: if (BMP_counter1) graphics.DrawImage(BMP_counter1, 190, 376); break;
		case 2: if (BMP_counter2) graphics.DrawImage(BMP_counter2, 190, 376); break;
		case 3: if (BMP_counter3) graphics.DrawImage(BMP_counter3, 190, 376); break;
		case 4: if (BMP_counter4) graphics.DrawImage(BMP_counter4, 190, 376); break;
		case 5: if (BMP_counter5) graphics.DrawImage(BMP_counter5, 190, 376); break;
		case 6: if (BMP_counter6) graphics.DrawImage(BMP_counter6, 190, 376); break;
		case 7: if (BMP_counter7) graphics.DrawImage(BMP_counter7, 190, 376); break;
		case 8: if (BMP_counter8) graphics.DrawImage(BMP_counter8, 190, 376); break;
		case 9: if (BMP_counter9) graphics.DrawImage(BMP_counter9, 190, 376); break;
		}
		
		firstDigit = timer / 10;
		secondDigit = timer % 10;

		switch (firstDigit)
		{
		case 0: if (BMP_counter0) graphics.DrawImage(BMP_counter0, 380, 376); break;
		case 1: if (BMP_counter1) graphics.DrawImage(BMP_counter1, 380, 376); break;
		case 2: if (BMP_counter2) graphics.DrawImage(BMP_counter2, 380, 376); break;
		case 3: if (BMP_counter3) graphics.DrawImage(BMP_counter3, 380, 376); break;
		case 4: if (BMP_counter4) graphics.DrawImage(BMP_counter4, 380, 376); break;
		case 5: if (BMP_counter5) graphics.DrawImage(BMP_counter5, 380, 376); break;
		case 6: if (BMP_counter6) graphics.DrawImage(BMP_counter6, 380, 376); break;
		case 7: if (BMP_counter7) graphics.DrawImage(BMP_counter7, 380, 376); break;
		case 8: if (BMP_counter8) graphics.DrawImage(BMP_counter8, 380, 376); break;
		case 9: if (BMP_counter9) graphics.DrawImage(BMP_counter9, 380, 376); break;
		}

		switch (secondDigit)
		{
		case 0: if (BMP_counter0) graphics.DrawImage(BMP_counter0, 410, 376); break;
		case 1: if (BMP_counter1) graphics.DrawImage(BMP_counter1, 410, 376); break;
		case 2: if (BMP_counter2) graphics.DrawImage(BMP_counter2, 410, 376); break;
		case 3: if (BMP_counter3) graphics.DrawImage(BMP_counter3, 410, 376); break;
		case 4: if (BMP_counter4) graphics.DrawImage(BMP_counter4, 410, 376); break;
		case 5: if (BMP_counter5) graphics.DrawImage(BMP_counter5, 410, 376); break;
		case 6: if (BMP_counter6) graphics.DrawImage(BMP_counter6, 410, 376); break;
		case 7: if (BMP_counter7) graphics.DrawImage(BMP_counter7, 410, 376); break;
		case 8: if (BMP_counter8) graphics.DrawImage(BMP_counter8, 410, 376); break;
		case 9: if (BMP_counter9) graphics.DrawImage(BMP_counter9, 410, 376); break;
		}



		if (BMP_smily && BMP_smilyPressed && BMP_smilyDead)
		{
			if (gameOver) 
			{
				graphics.DrawImage(BMP_smilyDead, 270, 376);
				if (smilyPressed) graphics.DrawImage(BMP_smilyPressed, 270, 376);
			}
				

			else if (smilyPressed) graphics.DrawImage(BMP_smilyPressed, 270, 376);
			else graphics.DrawImage(BMP_smily, 270, 376);	

			
		}



		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CLOSE:
		iRet = MessageBox(hWnd, TEXT("Do you want to Exit"), TEXT("Exit"), MB_YESNO);
		if (iRet == IDYES) SendMessage(hWnd, WM_DESTROY, 0, 0);
		break;
		break;
	case WM_DESTROY:

		PostQuitMessage(0);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

Bitmap* LoadPNGResource(HINSTANCE hInstance, UINT nResourceID)
{
	HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(nResourceID), L"PNG");
	if (!hRes) return nullptr;

	HGLOBAL hMem = LoadResource(hInstance, hRes);
	if (!hMem) return nullptr;

	void* pData = LockResource(hMem);
	if (!pData) return nullptr;

	DWORD size = SizeofResource(hInstance, hRes);
	if (size == 0) return nullptr;

	IStream* pStream = SHCreateMemStream((BYTE*)pData, size);
	if (!pStream) return nullptr;

	Bitmap* bmp = Bitmap::FromStream(pStream);
	pStream->Release();

	// Check if bitmap loaded successfully
	if (bmp && bmp->GetLastStatus() != Ok) {
		delete bmp;
		return nullptr;
	}

	return bmp;
}

void restartGame(HWND hwnd)
{
	for (int i = 0; i < 10; i++)
	{
		minesX[i] = rand() % 10;
		minesY[i] = rand() % 10;
	}


	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			boxes[x][y] = 0;
		}
	}

	for (int x = 0; x <= 10; x++) {
		boxes[minesX[x]][minesY[x]] = -1;
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (boxes[x][y] == -1)
			{
				if (x + 1 < 10 && boxes[x + 1][y] != -1) boxes[x + 1][y]++;
				if (x - 1 >= 0 && boxes[x - 1][y] != -1) boxes[x - 1][y]++;
				if (y + 1 < 10 && boxes[x][y + 1] != -1) boxes[x][y + 1]++;
				if (y - 1 >= 0 && boxes[x][y - 1] != -1) boxes[x][y - 1]++;

				if (x + 1 < 10 && y + 1 < 10 && boxes[x + 1][y + 1] != -1) boxes[x + 1][y + 1]++;
				if (x + 1 < 10 && y - 1 >= 0 && boxes[x + 1][y - 1] != -1) boxes[x + 1][y - 1]++;
				if (x - 1 >= 0 && y + 1 < 10 && boxes[x - 1][y + 1] != -1) boxes[x - 1][y + 1]++;
				if (x - 1 >= 0 && y - 1 >= 0 && boxes[x - 1][y - 1] != -1) boxes[x - 1][y - 1]++;
			}
		}
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			boxes[x][y] += 100;
		}
	}

	gameOver = false;
	victory = false;
	clickable = true;
	flagCounter = 10;
	timer = 99;
	revealedCount = 0;
	SetTimer(hwnd, 3, 1000, NULL);
}

# Scrollbar

* �ؼ���Ҫ���� Scrollbar Position �� Content Lines ��ӳ���ϵ

* ֻҪ�� CreateWindow �м��� WS_VSCROLL ���ܿ��������������Ƴ�����

* �������д����� nPage ֵ��������������ʾ��

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 100;
		si.nPage = 20;
		SetScrollInfo(hWnd, SB_VERT, &si, true);

* ��� fMask Ϊ�գ����ò��� nMin �� nMax ��ֵ������������ 0xFFFFFFFFCCCCCCCC��
		si.fMask = SIF_RANGE;
		GetScrollInfo(hWnd, SB_VERT, &si);

* ���չ������ƶ���ʱ��

	SB_THUMBTRACK - Ŀ��λ��
	SB_ENDSCROLL - ���ƶ���ʱ��
	SB_THUMBPOSITION - SB_ENDSCROLL ֮ǰͣ������λ��

	SB_THUMBPOSITION �������ƶ���ʱ�򲻸��¿ͻ�����ͣ������ʱ���ٸ��£����� SB_THUMBTRACK
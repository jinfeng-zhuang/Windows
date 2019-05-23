# Scrollbar

* 关键是要建立 Scrollbar Position 和 Content Lines 的映射关系

* 只要在 CreateWindow 中加入 WS_VSCROLL 就能看到滚动条被绘制出来。

* 如果不填写合理的 nPage 值，滚动条不会显示：

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 100;
		si.nPage = 20;
		SetScrollInfo(hWnd, SB_VERT, &si, true);

* 如果 fMask 为空，将拿不到 nMin 和 nMax 的值，读出来的是 0xFFFFFFFFCCCCCCCC：
		si.fMask = SIF_RANGE;
		GetScrollInfo(hWnd, SB_VERT, &si);

* 按照滚动条移动的时候：

	SB_THUMBTRACK - 目标位置
	SB_ENDSCROLL - 不移动的时候
	SB_THUMBPOSITION - SB_ENDSCROLL 之前停下来的位置

	SB_THUMBPOSITION 有助于移动的时候不更新客户区，停下来的时候再更新，忽略 SB_THUMBTRACK
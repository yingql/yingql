package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.sprite.BuyItemLine;

public class BuyClockItemLayer extends BuyItemLayer
{
	@Override
	public int getTitleBgId()
	{
		return R.drawable.buy_item_clock_title;
	}

	@Override
	public int getItemIconId()
	{
		return R.drawable.clock;
	}

	@Override
	public void close()
	{
		GameScene.getInstance().hideBuyClockItemLayer();
	}

	@Override
	public void initBuyItemLines(float x, float y)
	{
		BuyItemLine line1 = new BuyItemLine(BuyItemLine.TYPE_CLOCK, getItemIconId(), 1, 50, false);
		line1.setAnchorPercent(0, 0);
		line1.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(164)));
		this.addChild(line1, 1);
		line1.autoRelease();

		BuyItemLine line2 = new BuyItemLine(BuyItemLine.TYPE_CLOCK, getItemIconId(), 5, 150, false);
		line2.setAnchorPercent(0, 0);
		line2.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(134)));
		this.addChild(line2, 1);
		line2.autoRelease();

		BuyItemLine line3 = new BuyItemLine(BuyItemLine.TYPE_CLOCK, getItemIconId(), 10, 250, false);
		line3.setAnchorPercent(0, 0);
		line3.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(104)));
		this.addChild(line3, 1);
		line3.autoRelease();

		BuyItemLine line4 = new BuyItemLine(BuyItemLine.TYPE_CLOCK, getItemIconId(), 20, 400, true);
		line4.setAnchorPercent(0, 0);
		line4.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(74)));
		this.addChild(line4, 1);
		line4.autoRelease();
	}
}

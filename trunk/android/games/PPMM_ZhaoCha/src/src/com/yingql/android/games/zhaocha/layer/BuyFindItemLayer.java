package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.sprite.BuyItemLine;

public class BuyFindItemLayer extends BuyItemLayer
{
	@Override
	public int getTitleBgId()
	{
		return R.drawable.buy_item_find_title;
	}

	@Override
	public int getItemIconId()
	{
		return R.drawable.find;
	}

	@Override
	public void close()
	{
		GameScene.getInstance().hideBuyFindItemLayer();
	}

	@Override
	public void initBuyItemLines(float x, float y)
	{
		BuyItemLine line1 = new BuyItemLine(BuyItemLine.TYPE_FIND, getItemIconId(), 1, 20, false);
		line1.setAnchorPercent(0, 0);
		line1.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(164)));
		this.addChild(line1, 1);
		line1.autoRelease();

		BuyItemLine line2 = new BuyItemLine(BuyItemLine.TYPE_FIND, getItemIconId(), 5, 60, false);
		line2.setAnchorPercent(0, 0);
		line2.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(134)));
		this.addChild(line2, 1);
		line2.autoRelease();

		BuyItemLine line3 = new BuyItemLine(BuyItemLine.TYPE_FIND, getItemIconId(), 10, 100, false);
		line3.setAnchorPercent(0, 0);
		line3.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(104)));
		this.addChild(line3, 1);
		line3.autoRelease();

		BuyItemLine line4 = new BuyItemLine(BuyItemLine.TYPE_FIND, getItemIconId(), 20, 160, true);
		line4.setAnchorPercent(0, 0);
		line4.setPosition(WYPoint.make(x + ResolutionIndependent.resolveDp(16), y + ResolutionIndependent.resolveDp(74)));
		this.addChild(line4, 1);
		line4.autoRelease();
	}
}

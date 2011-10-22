package com.yingql.android.games.zhaocha.sprite;

import com.wiyun.engine.nodes.AtlasLabel;
import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Node;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;

public abstract class ItemButton extends Node
{
	protected int count = 0;
	protected AtlasLabel lbCount;
	protected GameInfoBoard board;

	public ItemButton(GameInfoBoard board)
	{
		this.board = board;

		Button btnItem = Button.make(getBgId(), 0, this, "useItem");
		btnItem.setAnchorPercent(0, 0);
		this.addChild(btnItem);
		btnItem.autoRelease();

		Button btnBuyItem = Button.make(R.drawable.btn_add_normal, R.drawable.btn_add_active, this, "buyItem");
		btnBuyItem.setAnchorPercent(0, 0);
		btnBuyItem.setPosition(ResolutionIndependent.resolve(WYPoint.make(51, 0)));
		this.addChild(btnBuyItem);
		btnBuyItem.autoRelease();

		Texture2D texture = Texture2D.makePNG(R.drawable.numbers);
		lbCount = AtlasLabel.make("0", texture, GameSystem.WhiteCharMap);
		lbCount.setAnchorPercent(1, 0f);
		lbCount.setPosition(ResolutionIndependent.resolve(WYPoint.make(48, 4)));
		this.addChild(lbCount);
		lbCount.autoRelease();
	}

	public int getCount()
	{
		return count;
	}

	public void setCount(int count)
	{
		this.count = count;
		if (lbCount != null)
		{
			lbCount.setText(count + "");
		}
	}

	public abstract int getBgId();

	public abstract void useItem();

	public abstract void buyItem();
}

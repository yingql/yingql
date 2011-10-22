package com.yingql.android.games.zhaocha.core;

import java.io.DataInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.entity.Archive;
import com.yingql.android.games.zhaocha.entity.LevelInfo;
import com.yingql.android.games.zhaocha.entity.PieceInfo;
import com.yingql.android.games.zhaocha.util.GameUtil;

public class LevelGenerator
{
	private static ConcurrentHashMap<Integer, List<PieceInfo>> caches = new ConcurrentHashMap<Integer, List<PieceInfo>>();

	/**
	 * 获取索引对应的图片的所有茬的信息
	 * 
	 * @param index
	 * @return
	 */
	private static List<PieceInfo> getPieceInfos(int index)
	{
		if (!caches.contains(index))
		{
			String fileName = index + ".map";
			List<PieceInfo> pieces = init(fileName, index);
			caches.put(index, pieces);
		}
		return caches.get(index);
	}

	/**
	 * 随机5个茬
	 * 
	 * @param all
	 * @param result
	 */
	private static void randFivePieces(List<PieceInfo> allPieces, List<PieceInfo> result)
	{
		// 随机从中选择5张错误图片
		if (allPieces.size() < 5)
			return;
		result.clear();
		while (result.size() < 5)
		{
			int randIndex = GameUtil.getRand().nextInt(allPieces.size());
			PieceInfo piece = allPieces.get(randIndex);
			piece.setFind(false);
			if (!result.contains(piece))
			{
				// 保证不随机出2个相交或者包含的茬，以提高用户体验
				boolean isIntersect = false;
				for (PieceInfo pieceInfo : result)
				{
					if (pieceInfo.getRect().isIntersect(piece.getRect()) || pieceInfo.getRect().containsRect(piece.getRect())
							|| piece.getRect().containsRect(pieceInfo.getRect()))
					{
						isIntersect = true;
						break;
					}
				}
				if (!isIntersect)
					result.add(piece);
			}
		}
	}

	/**
	 * 初始化地图信息
	 * 
	 * @param fileName
	 */
	private static List<PieceInfo> init(String fileName, int imageIndex)
	{
		InputStream in = null;
		DataInputStream input = null;
		List<PieceInfo> pieces = new ArrayList<PieceInfo>();
		try
		{
			in = MainActivity.Instance.getAssets().open(fileName);
			input = new DataInputStream(in);
			String line = null;
			int index = 1;
			while ((line = input.readLine()) != null)
			{
				String[] values = line.split(",");
				if (values.length == 4)
				{
					PieceInfo info = new PieceInfo();
					info.x = Float.parseFloat(values[0]);
					info.y = Float.parseFloat(values[1]);
					info.width = Float.parseFloat(values[2]);
					info.height = Float.parseFloat(values[3]);
					info.setImageIndex(index);
					info.setResPath(String.format("maps/image%d_cha%d.jpg", imageIndex, index));
					pieces.add(info);
					index++;
				}
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			GameUtil.closeStream(in);
			GameUtil.closeStream(input);
		}
		return pieces;
	}

	/**
	 * 随机一个关卡信息
	 * 
	 * @return
	 */
	public static LevelInfo rand()
	{
		LevelInfo info = new LevelInfo();
		int index = GameUtil.getRand().nextInt(GameSystem.IMAGE_COUNT) + 1;
		info.setImageIndex(index);
		info.setResPath(String.format("maps/image%d.jpg", index));
		List<PieceInfo> allPieces = getPieceInfos(index);
		randFivePieces(allPieces, info.getPieces());
		return info;
	}

	/**
	 * 根据进度获取关卡信息
	 * 
	 * @param archive
	 * @return
	 */
	public static LevelInfo getByArchive(Archive archive)
	{
		LevelInfo info = new LevelInfo();
		int index = archive.getMapIndex();
		info.setImageIndex(index);
		info.setResPath(String.format("maps/image%d.jpg", index));
		List<PieceInfo> allPieces = getPieceInfos(index);
		List<PieceInfo> result = info.getPieces();
		for (PieceInfo pieceInfo : allPieces)
		{
			if (archive.getPieces().contains(pieceInfo.getImageIndex()))
			{
				if (archive.getFoundPieces().contains(pieceInfo.getImageIndex()))
					pieceInfo.setFind(true);
				else
					pieceInfo.setFind(false);
				result.add(pieceInfo);
			}
		}
		return info;
	}
}

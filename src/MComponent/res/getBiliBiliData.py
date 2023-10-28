from bilibili_api import user, Credential
import asyncio
import json
import sys

# 图标url
# UID
# 用户名
# 等级
# 硬币
# 关注
# 粉丝
# 点赞
# 播放
# 阅读

# 需要返回的数据
shouldInfo = {
    'iconUrl': '--',
    'userName': '--',
    'uid': '--',
    'level': '--',
    'coinCount': '--',
    'followCount': '--',
    'fansCount': '--',
    'likeCount': '--',
    'playCount': '--',
    'readCount': '--'
}


async def main() -> None:
    CREDENTIAL = Credential(
        sessdata=arguments[0],
        bili_jct=arguments[1]
    )

    bilibiliApi = user.User(uid=int(arguments[2]), credential=CREDENTIAL)
    userInfo = await bilibiliApi.get_user_info()
    relationInfo = await bilibiliApi.get_relation_info()
    upInfo = await bilibiliApi.get_up_stat()

    shouldInfo['iconUrl'] = userInfo['face']
    shouldInfo['userName'] = userInfo['name']
    shouldInfo['uid'] = userInfo['mid']
    shouldInfo['level'] = userInfo['level']
    shouldInfo['coinCount'] = userInfo['coins']
    shouldInfo['followCount'] = relationInfo['following']
    shouldInfo['fansCount'] = relationInfo['follower']
    shouldInfo['likeCount'] = upInfo['likes']
    shouldInfo['playCount'] = upInfo['archive']['view']
    shouldInfo['readCount'] = upInfo['article']['view']

    # 将字典写入JSON文件
    with open(arguments[3], "w") as file:
        json.dump(shouldInfo, file)

# 传入参数: sessdata bili_jct json脚本绝对路径
if __name__ == '__main__':

    # 获取命令行参数
    arguments = sys.argv
    arguments = arguments[1:]

    print(arguments)
    asyncio.run(main())

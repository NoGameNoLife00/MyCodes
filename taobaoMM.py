# -*- coding:utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

import urllib
import urllib2
import re
import os

class Tool:
    removeImg = re.compile('<img.*?>| {7}|')    # 图片
    removeURL = re.compile('<a.*?>|</a>')   # 连接
    removeLine = re.compile('<tr>|<div>|</div>|</p>')  # 换行
    removeTD = re.compile('<td>')   # 表格
    removePara = re.compile('<p.*?>')   # 段落开头
    removeBR = re.compile('<br><br>|<br>')  # 换行，双换行
    removeExtraTag = re.compile('<.*?>')    # 标签

    def replace(self, x):
        x = re.sub(self.removeImg, "", x)
        x = re.sub(self.removeURL, "", x)
        x = re.sub(self.removeLine, "\n", x)
        x = re.sub(self.removeTD, '\t', x)
        x = re.sub(self.removePara, '\n    ', x)
        x = re.sub(self.removeBR, '\n', x)
        x = re.sub(self.removeExtraTag, "", x)
        return x.strip()


class TaobaoSpider:
    def __init__(self):
        self.url = 'http://mm.taobao.com/json/request_top_list.htm'
        self.tool = Tool()

    def getPage(self, pageNum):
        url = self.url + "?page=" + str(pageNum)
        print url
        request = urllib2.Request(url)
        response = urllib2.urlopen(request)
        return response.read().decode('gbk')

    def getContents(self, pageNum):
        page = self.getPage(pageNum)
        pattern = re.compile('<div class="list-item">.*?pic-word.*?<a href="(.*?)".*?<img src="(.*?)".*?<a class="lady-name" href="(.*?)".*?>(.*?)</a>.*?<strong>(.*?)</strong>.*?<span>(.*?)</span>',
                             re.S)
        items = re.findall(pattern, page)
        contents = []
        for item in items:
            contents.append([item[0], item[1], item[2], item[3], item[4], item[5]])
        return  contents

    def getInfoPage(self, infoURL):
        response = urllib2.urlopen(infoURL)
        return response.read().decode('gbk')

    # 获取淘宝MM爱秀详情
    def getBrief(self, page):
        pattern = re.compile('<div class="mm-aixiu-content.*?>(.*?)<!--', re.S)
        result = re.search(pattern, page)
        return self.tool.replace(result.group(1))

    def getAllImg(self, page):
        pattern = re.compile('<div class="mm-aixiu-content.*?>(.*?)<!--', re.S)
        content = re.search(pattern, page).group(1)
        patternImg = re.compile('<img.*?src="(.*?)"', re.S)
        imgs = re.findall(patternImg, content)
        return imgs

    def saveImgs(self, images, name):
        num = 1
        print "%s（爱秀）共有%d张照片" % (name, len(images))
        for imgURL in images:
            splitPath = imgURL.split('.')
            fileTail = splitPath.pop()
            if len(fileTail) > 3:
                fileTail = 'jpg'
            fileName = name + "/" + str(num) + "." + fileTail
            self.saveImg("http:"+imgURL, fileName)
            num += 1

    def saveHeadPortrait(self, headURL, name):
        splitPath = headURL.split('.')
        fileTail = splitPath.pop()
        fileName = name + "/icon." + fileTail
        self.saveImg(headURL, fileName)

    def saveBrief(self, content, name):
        filename = name + "/" + name + ".txt"
        f = open(filename, "w+")
        print "保存%s的个人信息" % filename
        f.write(content.decode("utf-8"))


    def saveImg(self, imageURL, fileName):
        u = urllib.urlopen(imageURL)
        data = u.read()
        f = open(fileName, 'wb')
        f.write(data)
        f.close()


    def saveBrief(self, content, name):
        fileName = name+'/'+name+'.txt'
        f = open(fileName, "w+")
        print u"保存%s的信息中" % name
        f.write(content)

    def mkDir(self, path):
        path = path.strip()
        isExists = os.path.exists(path)
        if not isExists:
            print u"创建(%s)的文件夹" % path
            os.makedirs(path)
            return True
        else:
            print u"%s文件夹已经创建" % path
            return False

    def savePageInfo(self, pageIndex):
        contents = self.getContents(pageIndex)
        for item in contents:
            print u"模特：%s 年龄：%s 地址: %s" % (item[3], item[4], item[5])
            print u"爱秀地址为 ", item[0]
            print u"保存%s的信息中" % item[3]
            detailURL = "http:" + item[0]
            detailPage = self.getInfoPage(detailURL)
            brief = self.getBrief(detailPage)
            imges = self.getAllImg(detailPage)
            if self.mkDir(item[3]):
                self.saveBrief(brief, item[3])
                self.saveHeadPortrait("http:"+item[1], item[3])
                self.saveImgs(imges, item[3])

    def savePagesInfo(self, start, end):
        for i in range(start, end):
            print u"保存第%d页中" % i
            self.savePageInfo(i)


spider = TaobaoSpider()
spider.savePagesInfo(1, 20)


package com.test.service.impl;

import com.test.model.UserModel;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Repository;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * 用户管理
 */
@Component
public class UserServiceImpl {

    private static final Logger LOGGER = LoggerFactory.getLogger(UserServiceImpl.class);

    private List<UserModel> allUserList = Collections.synchronizedList(new ArrayList<UserModel>());

    @PostConstruct
    public void init() {
        String rootPath = System.getProperty("web.root");
        String configPath = rootPath  + "conf" + File.separatorChar + "config.xml";
        // 读取用户配置
        DocumentBuilder db = null;
        DocumentBuilderFactory dbf = null;
        Element element = null;
        UserModel newUser;


        try {
            File configFile = new File(configPath);
            dbf = DocumentBuilderFactory.newInstance();
            db = dbf.newDocumentBuilder();

            String name = null;
            String password = null;
            Document doc = db.parse(configFile);
            NodeList userList = doc.getElementsByTagName("User");
            for (int i = 0; i < userList.getLength(); i++) {
                NodeList userAttrs = userList.item(i).getChildNodes();
                for (int j = 0; j < userAttrs.getLength(); j++) {
                    String tagName  = userAttrs.item(j).getNodeName();

                    if (tagName == "name") {
                        name = userAttrs.item(j).getChildNodes().item(0).getNodeValue().trim();
                    }

                    if (tagName == "password") {
                        password = userAttrs.item(j).getChildNodes().item(0).getNodeValue().trim();
                    }

                }

                if (name != null && password != null) {
                    newUser = new UserModel(name, password);
                    addUser(newUser);
                }
            }
        } catch (Exception e) {
            LOGGER.error("Config init failure", e);
        }
    }

    @PreDestroy
    public void destroy() {

    }

    synchronized public void addUser(UserModel user) {
        allUserList.add(user);
    }

    synchronized public void removeUser(String userName) {
        for (int i = allUserList.size() - 1; i >= 0; i--) {
            UserModel user = allUserList.get(i);
            if (user != null && allUserList.get(i).getUsername().equals(userName)) {
                allUserList.remove(i);
            }
        }
    }

    public UserModel findUserByName(String userName) {
        for (int i = allUserList.size() - 1; i >= 0; i--) {
            UserModel user = allUserList.get(i);
            if (user != null && allUserList.get(i).getUsername().equals(userName)) {

                return allUserList.get(i);
            }
        }
        return null;
    }
}

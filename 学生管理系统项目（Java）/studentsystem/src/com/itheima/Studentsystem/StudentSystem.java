package com.itheima.Studentsystem;

import java.util.ArrayList;
import java.util.Scanner;

public class StudentSystem {
    public static void main(String[] args) {
        ArrayList<Student> list = new ArrayList<>();
        loop: while (true) {
            System.out.println("-----------欢迎来到学生管理系统------------");
            System.out.println("1:添加学生");
            System.out.println("2:删除学生");
            System.out.println("3:修改学生");
            System.out.println("4:查询学生");
            System.out.println("5:退出");
            System.out.println("请输入您的选择：");
            Scanner sc = new Scanner(System.in);
            String choose = sc.next();
            switch (choose) {
                case "1" -> addStudent(list);
                case "2" -> deleteStudent(list);
                case "3" -> updateStudent(list);
                case "4" -> qyeryStudent(list);
                case "5" -> {
                    System.out.println("退出");
                    break loop;
                }
                default -> System.out.println("没有这个选项");
            }
        }

    }




    public static void addStudent(ArrayList<Student> list) {
        Student s = new Student();

        Scanner sc = new Scanner(System.in);
        String id = null;
        while (true) {
            System.out.println("请输入学生id");
            id = sc.next();
            boolean flag=comtains(list, id);
            if (flag) {
                System.out.println("id已经存在，请重新录入");
            }else{
                s.setId(id);
                break;
            }
        }
        s.setId(id);
        System.out.println("请输入学生姓名");
        String name = sc.next();
        s.setName(name);
        System.out.println("请输入学生年龄");
        int age = sc.nextInt();
        s.setAge(age);
        System.out.println("请输入学生家庭地址");
        String address = sc.next();
        s.setAddress(address);
        list.add(s);
        System.out.println("学生信息添加成功");
    }
    public static void deleteStudent(ArrayList<Student> list) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入要删除的id");
        String id = sc.next();
        int index = getIndex(list, id);
        if(index>=0){
            list.remove(index);
            System.out.println("id为:"+id+"的学生删除成功");
        }else{
            System.out.println("id不存在，删除失败");
        }
    }
    public static void updateStudent(ArrayList<Student> list) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入要修改学生的id");
        String id = sc.next();
        int index = getIndex(list, id);
        if(index==-1){
            System.out.println("要修改的id"+id+"不存在，请重新输入");
            return;
        }
        Student stu=list.get(index);
        System.out.println("请输入要修改的学生姓名");
        String newName = sc.next();
        stu.setName(newName);
        System.out.println("请输入要修改的学生年龄");
        int newAge = sc.nextInt();
        stu.setAge(newAge);
        System.out.println("请输入修改的学生家庭住址");
        String newAddress = sc.next();
        stu.setAddress(newAddress);
        System.out.println("学生信息修改成功");
    }
    public static void qyeryStudent(ArrayList<Student> list) {
        if(list.size()==0){
            System.out.println("当前无学生信息，请添加后再查询");
            return;
        }
        System.out.println("id\t\t姓名\t年龄\t家庭住址");
        for(int i=0;i<list.size();i++){
            Student stu=list.get(i);
            System.out.println(stu.getId()+"\t"+stu.getName()+"\t"+stu.getAge()+"\t"+stu.getAddress());
        }


    }

    public static boolean comtains(ArrayList<Student> list,String id){
//        for (int i = 0; i < list.size(); i++) {
//            Student stu = list.get(i);
//            String sid = stu.getId();
//            if (sid.equals(id)) {
//                return true;
//            }
//        }
//        return false;
        return getIndex(list,id)!=-1;
    }

    public static int getIndex(ArrayList<Student> list,String id){
        for (int i = 0; i < list.size(); i++) {
            Student stu = list.get(i);
            String sid = stu.getId();
            if (sid.equals(id)) {
                return i;
            }
        }
        return -1;
    }





}

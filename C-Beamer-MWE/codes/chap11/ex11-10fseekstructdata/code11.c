bool ModifyDataFile(const char *filename)
{
    FILE *fp;
    fpos_t pos;
    StuNode stu = {0};
    // 打开文件，二进制文件读/写模式
    fp = fopen(filename, "rb+");
    ...
    fseek(fp, 2L * sizeof(stu), SEEK_SET); // 向前偏移2个元素
    fread(&stu, sizeof(stu), 1, fp);
    fgetpos(fp, &pos); // 记录当前位置

    strcpy(stu.name, "ModifyName");
    fseek(fp, -1L * sizeof(stu), SEEK_CUR); // 向后偏移1个元素
    fwrite(&stu, sizeof(stu), 1, fp);

    rewind(fp); // 回退到文件开始位置
    fread(&stu, sizeof(stu), 1, fp);
    strcpy(stu.name, "First");
    fseek(fp, -1L * sizeof(stu), SEEK_CUR); // 向后偏移1个元素
    fwrite(&stu, sizeof(stu), 1, fp);

    fsetpos(fp, &pos); // 设置前面记录的位置
    fread(&stu, sizeof(stu), 1, fp);
    strcpy(stu.name, "SetPos");
    fseek(fp, -1L * sizeof(stu), SEEK_CUR); // 向后偏移1个元素
    fwrite(&stu, sizeof(stu), 1, fp);

    fclose(fp); // 关闭文件
    return true;
}

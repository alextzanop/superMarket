a.out:
	@clear
	@gcc -Wall main.c 
	@./a.out ../../cs240_testfiles_projectb_20190414/test_1.txt
	@read -n 1 -p "Press any key for next test(2): "
	@./a.out ../../cs240_testfiles_projectb_20190414/test_2.txt
	@read -n 1 -p "Press any key for next test(3): "
	@./a.out ../../cs240_testfiles_projectb_20190414/test_3.txt
	@read -n 1 -p "Press any key for next test(4): "
	@./a.out ../../cs240_testfiles_projectb_20190414/test_4.txt
	@read -n 1 -p "Press any key for next test(5): "
	@./a.out ../../cs240_testfiles_projectb_20190414/test_5.txt
	@read -n 1 -p "Press any key for next test(6): "
	@./a.out ../../cs240_testfiles_projectb_20190414/test_6.txt
	@read -n 1 -p "Press any key for next test(7):
	@./a.out ../../cs240_testfiles_projectb_20190414/test_7.txt
	@read -n 1 -p "Press any key for next test(8): "
	@./a.out ../../cs240_testfiles_projectb_20190414/test_8.txt
	@rm a.out
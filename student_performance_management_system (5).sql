-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 24, 2025 at 11:55 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `student performance management system`
--

-- --------------------------------------------------------

--
-- Table structure for table `courses`
--

CREATE TABLE `courses` (
  `course_id` int(11) NOT NULL,
  `course_name` varchar(100) NOT NULL,
  `course_code` varchar(20) NOT NULL,
  `credits` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `courses`
--

INSERT INTO `courses` (`course_id`, `course_name`, `course_code`, `credits`) VALUES
(1, 'Database', 'BITI1123', 3),
(2, 'Computer Networks', 'CSC2003', 3),
(3, 'Programming Fundamentals', 'CSC1002', 3),
(4, 'Operating Systems', 'CSC3008', 3),
(5, 'Digital Animation', 'DAN3001', 2),
(6, 'Web Development', 'BITI3306', 3),
(7, 'Falsafah', 'BITI4001', 3),
(8, 'Computer Sains', 'BITI 3310', 3);

-- --------------------------------------------------------

--
-- Table structure for table `course_lecturer`
--

CREATE TABLE `course_lecturer` (
  `course_id` int(11) NOT NULL,
  `lecturer_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `course_lecturer`
--

INSERT INTO `course_lecturer` (`course_id`, `lecturer_id`) VALUES
(1, 19),
(1, 28),
(1, 30),
(2, 19),
(2, 28),
(2, 29),
(3, 19),
(3, 28),
(4, 19),
(5, 19),
(6, 28);

-- --------------------------------------------------------

--
-- Table structure for table `department`
--

CREATE TABLE `department` (
  `department_id` int(11) NOT NULL,
  `department_name` varchar(100) NOT NULL,
  `lecturer_id` int(11) DEFAULT NULL,
  `department_short_name` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `department`
--

INSERT INTO `department` (`department_id`, `department_name`, `lecturer_id`, `department_short_name`) VALUES
(1, 'Faculty of Computer Science and Information Technology', 19, 'FKOM'),
(5, 'Faculty of Science and Technology ', 25, 'FST'),
(6, 'Faculty of Management and Human Resource Development ', 26, 'FPPSM'),
(7, 'Faculty of Mechanical Engineering ', 27, 'FKM'),
(8, 'Faculty of Science and Technology ', 28, 'FST'),
(9, 'Faculty of Science and Technology ', 29, 'FST'),
(10, 'Faculty of Science and Technology ', 30, 'FST');

-- --------------------------------------------------------

--
-- Table structure for table `feedback`
--

CREATE TABLE `feedback` (
  `feedback_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `feedback_type` enum('System feedback','Course feedback') NOT NULL,
  `course_id` int(11) DEFAULT NULL,
  `feedback_text` text NOT NULL,
  `date_submitted` datetime DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `feedback`
--

INSERT INTO `feedback` (`feedback_id`, `user_id`, `feedback_type`, `course_id`, `feedback_text`, `date_submitted`) VALUES
(9, 7, 'Course feedback', 1, 'good subject', '2025-01-06 14:01:42'),
(10, 7, 'Course feedback', 2, 'good subject', '2025-01-06 14:06:53'),
(11, 7, 'System feedback', 1, 'good system', '2025-01-06 14:08:50'),
(12, 7, 'Course feedback', 1, 'good subject', '2025-01-09 16:49:03'),
(13, 7, 'Course feedback', 2, 'good subject', '2025-01-16 22:00:32'),
(14, 7, 'Course feedback', 2, 'good subject', '2025-01-16 22:04:26'),
(15, 7, 'System feedback', 1, 'good subject', '2025-01-16 22:05:22'),
(16, 7, 'Course feedback', 1, 'good subject', '2025-01-24 10:07:12'),
(20, 21, 'Course feedback', 1, 'good subject', '2025-01-24 10:49:19'),
(21, 7, 'Course feedback', 1, 'good subject', '2025-01-24 12:00:00');

-- --------------------------------------------------------

--
-- Table structure for table `grade_definitions`
--

CREATE TABLE `grade_definitions` (
  `grade_id` int(11) NOT NULL,
  `grade` varchar(5) NOT NULL,
  `min_score` int(11) NOT NULL,
  `max_score` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `grade_definitions`
--

INSERT INTO `grade_definitions` (`grade_id`, `grade`, `min_score`, `max_score`) VALUES
(1, 'A+', 90, 100),
(2, 'A', 80, 89),
(3, 'A-', 75, 79),
(4, 'B+', 70, 74),
(5, 'B', 65, 69),
(6, 'B-', 60, 64),
(7, 'C+', 55, 59),
(8, 'C', 50, 54),
(9, 'C-', 45, 49),
(13, 'D+', 40, 44),
(14, 'D', 35, 39),
(15, 'D-', 30, 34),
(16, 'F', 0, 29);

-- --------------------------------------------------------

--
-- Table structure for table `scores`
--

CREATE TABLE `scores` (
  `score_id` int(11) NOT NULL,
  `student_id` int(11) NOT NULL,
  `course_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `scores`
--

INSERT INTO `scores` (`score_id`, `student_id`, `course_id`) VALUES
(2, 7, 2),
(10, 5, 2),
(11, 7, 1),
(12, 5, 1),
(13, 8, 1),
(14, 5, 5),
(15, 6, 1),
(16, 6, 2),
(17, 8, 2),
(18, 9, 1),
(19, 10, 1),
(20, 12, 1),
(21, 11, 1),
(22, 13, 1),
(23, 14, 1),
(24, 16, 1),
(25, 17, 1),
(26, 20, 1),
(28, 21, 1),
(29, 9, 2),
(30, 40, 1),
(32, 41, 1);

-- --------------------------------------------------------

--
-- Table structure for table `score_mark`
--

CREATE TABLE `score_mark` (
  `mark_ID` int(11) NOT NULL,
  `score_id` int(11) NOT NULL,
  `mark` double NOT NULL,
  `score_type` int(11) NOT NULL,
  `date_score` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `score_mark`
--

INSERT INTO `score_mark` (`mark_ID`, `score_id`, `mark`, `score_type`, `date_score`) VALUES
(1, 11, 70, 1, '2025-01-07'),
(4, 11, 68, 3, '2025-01-07'),
(6, 11, 90, 5, '2025-01-08'),
(9, 11, 77, 7, '2025-01-08'),
(10, 12, 98, 5, '2025-01-08'),
(11, 13, 70, 2, '2025-01-08'),
(15, 12, 50, 1, '2025-01-08'),
(17, 12, 50, 2, '2025-01-08'),
(18, 11, 60, 2, '2025-01-08'),
(19, 13, 50, 5, '2025-01-09'),
(20, 12, 50, 7, '2025-01-09'),
(21, 12, 55, 4, '2025-01-09'),
(22, 13, 67, 1, '2025-01-09'),
(23, 11, 50, 4, '2025-01-11'),
(24, 2, 70, 1, '2025-01-12'),
(26, 2, 60, 2, '2025-01-12'),
(27, 2, 70, 3, '2025-01-12'),
(28, 11, 90, 6, '2025-01-16'),
(29, 15, 60, 1, '2025-01-23'),
(30, 18, 67, 1, '2025-01-23'),
(31, 19, 100, 1, '2025-01-23'),
(32, 20, 90, 1, '2025-01-23'),
(33, 21, 80, 1, '2025-01-23'),
(34, 22, 70, 1, '2025-01-23'),
(35, 23, 85, 1, '2025-01-23'),
(36, 24, 50, 1, '2025-01-23'),
(37, 25, 72, 1, '2025-01-23'),
(38, 26, 62, 1, '2025-01-23'),
(39, 28, 42, 1, '2025-01-23'),
(40, 15, 66, 2, '2025-01-23'),
(41, 18, 72, 2, '2025-01-23'),
(42, 19, 56, 2, '2025-01-23'),
(43, 21, 82, 2, '2025-01-23'),
(44, 20, 58, 2, '2025-01-23'),
(45, 22, 69, 2, '2025-01-23'),
(46, 23, 60, 2, '2025-01-23'),
(47, 24, 65, 2, '2025-01-23'),
(48, 25, 80, 2, '2025-01-23'),
(49, 26, 52, 2, '2025-01-23'),
(50, 28, 62, 2, '2025-01-23'),
(51, 12, 50, 3, '2025-01-23'),
(52, 15, 50, 3, '2025-01-23'),
(53, 13, 70, 3, '2025-01-23'),
(54, 18, 60, 3, '2025-01-23'),
(55, 19, 88, 3, '2025-01-23'),
(56, 21, 65, 3, '2025-01-23'),
(57, 20, 70, 3, '2025-01-23'),
(58, 22, 40, 3, '2025-01-23'),
(59, 23, 60, 3, '2025-01-23'),
(60, 24, 80, 3, '2025-01-23'),
(61, 25, 70, 3, '2025-01-23'),
(62, 26, 42, 3, '2025-01-23'),
(63, 28, 60, 3, '2025-01-23'),
(64, 15, 65, 4, '2025-01-23'),
(65, 13, 70, 4, '2025-01-23'),
(66, 18, 65, 4, '2025-01-23'),
(67, 19, 70, 4, '2025-01-23'),
(68, 21, 40, 4, '2025-01-23'),
(69, 20, 40, 4, '2025-01-23'),
(70, 22, 56, 4, '2025-01-23'),
(71, 23, 50, 4, '2025-01-23'),
(72, 24, 75, 4, '2025-01-23'),
(73, 25, 75, 4, '2025-01-23'),
(74, 26, 90, 4, '2025-01-23'),
(75, 28, 90, 4, '2025-01-23'),
(76, 15, 70, 5, '2025-01-23'),
(77, 18, 70, 5, '2025-01-23'),
(78, 19, 50, 5, '2025-01-23'),
(79, 21, 85, 5, '2025-01-23'),
(80, 20, 40, 5, '2025-01-23'),
(81, 22, 40, 5, '2025-01-23'),
(82, 23, 65, 5, '2025-01-23'),
(83, 24, 65, 5, '2025-01-23'),
(84, 25, 75, 5, '2025-01-23'),
(85, 26, 75, 5, '2025-01-23'),
(86, 28, 85, 5, '2025-01-23'),
(87, 12, 90, 6, '2025-01-23'),
(88, 15, 80, 6, '2025-01-23'),
(89, 13, 85, 6, '2025-01-23'),
(90, 18, 70, 6, '2025-01-23'),
(91, 19, 70, 6, '2025-01-23'),
(92, 21, 60, 6, '2025-01-23'),
(93, 20, 60, 6, '2025-01-23'),
(94, 22, 50, 6, '2025-01-23'),
(95, 23, 50, 6, '2025-01-23'),
(96, 24, 65, 6, '2025-01-23'),
(97, 25, 65, 6, '2025-01-23'),
(98, 26, 55, 6, '2025-01-23'),
(99, 28, 55, 6, '2025-01-23'),
(100, 15, 60, 7, '2025-01-23'),
(101, 13, 60, 7, '2025-01-23'),
(102, 18, 78, 7, '2025-01-23'),
(103, 19, 50, 7, '2025-01-23'),
(104, 21, 70, 7, '2025-01-23'),
(105, 20, 70, 7, '2025-01-23'),
(106, 22, 80, 7, '2025-01-23'),
(107, 23, 80, 7, '2025-01-23'),
(108, 24, 85, 7, '2025-01-23'),
(109, 25, 85, 7, '2025-01-23'),
(110, 26, 90, 7, '2025-01-23'),
(111, 28, 90, 7, '2025-01-23'),
(112, 10, 50, 1, '2025-01-24'),
(113, 30, 60, 1, '2025-01-24');

-- --------------------------------------------------------

--
-- Table structure for table `score_types`
--

CREATE TABLE `score_types` (
  `score_type_id` int(11) NOT NULL,
  `score_title` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `score_types`
--

INSERT INTO `score_types` (`score_type_id`, `score_title`) VALUES
(1, 'PBL1'),
(2, 'PBL2'),
(3, 'PBL3'),
(4, 'PBL4'),
(5, 'PBL5'),
(6, 'Final Exam'),
(7, 'Exercise');

-- --------------------------------------------------------

--
-- Table structure for table `students`
--

CREATE TABLE `students` (
  `student_id` int(11) NOT NULL,
  `enrollment_year` int(11) DEFAULT NULL,
  `major` varchar(50) DEFAULT NULL,
  `matrix_number` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `students`
--

INSERT INTO `students` (`student_id`, `enrollment_year`, `major`, `matrix_number`) VALUES
(5, 2024, 'Mathematics', 'MAT0005'),
(6, 2024, 'Physics', 'MAT0006'),
(7, 2024, 'Computer Science', 'MAT0007'),
(8, 2024, 'Architecture', 'MAT0008'),
(9, 2024, 'Marketing', 'MAT0009'),
(10, 2024, 'Architecture', 'MAT248'),
(11, 2024, 'Architecture', 'MAT249'),
(12, 2024, 'Law', 'MAT2410'),
(13, 2024, 'Data Science', 'MAT2411'),
(14, 2024, 'Architecture', 'MAT2412'),
(16, 2024, 'Biology', 'MAT2413'),
(17, 2024, 'Architecture', 'MAT2414'),
(20, 2025, 'Computer Science', 'MAT251'),
(21, 2025, 'Data Science', 'MAT252'),
(40, 2025, 'Computer Science', 'MAT253'),
(41, 2025, 'Computer Science', 'MAT254');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `user_id` int(11) NOT NULL,
  `user_type` enum('lecturer','student','admin') NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(255) NOT NULL,
  `first_name` varchar(50) NOT NULL,
  `last_name` varchar(50) NOT NULL,
  `email` varchar(100) NOT NULL,
  `phone_number` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`user_id`, `user_type`, `username`, `password`, `first_name`, `last_name`, `email`, `phone_number`) VALUES
(1, 'admin', 'admin123', 'khor4038', 'Khor', 'Soon Keat', 'soonkeat@gmail.com', '0177346547'),
(5, 'student', 'shinni123', 'khor4038', 'Khor', 'Shin Ni', 'shinni@gmail.com', '0198574687'),
(6, 'student', 'jiaqi2000', 'khor4038', 'Khor', 'Jia Qi', 'jiaqi@gmail.com', '0187564537'),
(7, 'student', 'yongkang123', 'khor4038', 'Lee', 'Yong Kang', 'yongkang@gmail.com', '0198574635'),
(8, 'student', 'yishen123', 'khor4038', 'Lee', 'Yi Shen', 'yishen@gmail.com', '0187678654'),
(9, 'student', 'yinghwa2001', 'khor4038', 'Lim', 'Ying Hwa', 'yinghwa@gmail.com', '0187648332'),
(10, 'student', 'kaishun123', 'khor4038', 'Teoh ', 'Kai Shun', 'kaishun@gmail.com', '0185544339'),
(11, 'student', 'guanhong123', 'khor4038', 'Lim', 'Guan Hong', 'guanhong@gmail.com', '0198574638'),
(12, 'student', 'kaixin2000', 'khor4038', 'Lim', 'Kai Xin', 'kaixin@gmail.com', '0198563774'),
(13, 'student', 'jiaern123', 'khor4038', 'Lee', 'Jia Ern', 'jiaern@gmail.com', '0198574663'),
(14, 'student', 'yeeern123', 'khor123', 'Khor', 'Yee Ern', 'yeeern@gmail.com', '0198576433'),
(16, 'student', 'sinyin123', 'khor4038', 'Goh', 'Sin Yin', 'sinyin@gmail.com', '0127458963'),
(17, 'student', 'peifei123', 'khor4038', 'Lee', 'Pei Fei', 'peifei@gmail.com', '0194567896'),
(19, 'lecturer', 'jiaxin123', 'khor4038', 'Lee ', 'Jia Xin', 'jiaxin@gmail.com', '0184433854'),
(20, 'student', 'yijing123', 'khor4038', 'Lim', 'Yi Jing', 'yijing@gmail.com', '0194939858'),
(21, 'student', 'jason123', 'khor4038', 'Chan', 'Jason', 'jason@gmail.com', '0198573824'),
(25, 'lecturer', 'jiamay123', 'khor4038', 'Lee', 'Jia May', 'jiamay@gmail.com', '0184574995'),
(26, 'lecturer', 'shingjou123', 'khor4038', 'Teh', 'Shing Jou', 'shingjou@gmail.com', '0187564738'),
(27, 'lecturer', 'boon123', 'khor4038', 'Boon', 'Shoung', 'shoung@gmail.com', '0112394857'),
(28, 'lecturer', 'shiken123', 'khor4038', 'Lee', 'Shi Ken', 'shiken@gmail.com', '0184444889'),
(29, 'lecturer', 'zhiying123', 'khor4038', 'Lee', 'Zhi Ying', 'zhiying@gmail.com', '0198674834'),
(30, 'lecturer', 'zhongwei123', 'khor4038', 'Lim', 'Zhong Wei', 'zhongwei@gmail.com', '0198574375'),
(31, 'lecturer', 'yingying123', 'khor4038', 'Lim', 'Ying Ying', 'yingying@gmail.com', '0186758334'),
(32, 'lecturer', 'huangcai123', 'khor4038', 'Lim', 'Huang Cai', 'huangcai@gmail.com', '0198574332'),
(33, 'lecturer', 'weily123', 'khor4038', 'Lim', 'Weily', 'weily@gmail.com', '0185757483'),
(35, 'lecturer', 'kaishen123', 'khor4038', 'Lee', 'Kai Shen', 'kaishen@gmail.com', '0195746374'),
(36, 'lecturer', 'yikai123', 'khor4038', 'Lee', 'Yi Kai', 'yikai@gmail.com', '0195858584'),
(37, 'lecturer', 'kaiyee123', 'khor4038', 'Lim', 'Kai Yee', 'kaiyee@gmail.com', '0185744747'),
(38, 'lecturer', 'yihong123', 'khor4038', 'Lee', 'Yi Hong', 'yihong@gmail.com', '0195858584'),
(39, 'lecturer', 'yihang123', 'khor4038', 'Lee', 'Yi Hang', 'yihang@gmail.com', '0198558549'),
(40, 'student', 'huaying123', 'khor4038', 'Lee ', 'Hua Ying', 'huaying@gmail.com', '0195867743'),
(41, 'student', 'jiahong123', 'khor4038', 'Lee', 'Jia Hong', 'jiahong@gmail.com', '0195858543'),
(42, 'student', 'jiachen123', 'khor4038', 'Lee ', 'Jia Chen', 'jiachen@gmail.com', '0198585854'),
(43, 'student', 'jiayi123', 'khor4038', 'Lee', 'Jia Yi', 'jiayi@gmail.com', '01986757483'),
(44, 'student', 'jiahao123', 'khor4038', 'Lee', 'Jia Hao', 'jiahao@gmail.com', '0185754499');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `courses`
--
ALTER TABLE `courses`
  ADD PRIMARY KEY (`course_id`),
  ADD UNIQUE KEY `course_code` (`course_code`);

--
-- Indexes for table `course_lecturer`
--
ALTER TABLE `course_lecturer`
  ADD PRIMARY KEY (`course_id`,`lecturer_id`),
  ADD KEY `lecturer_id` (`lecturer_id`);

--
-- Indexes for table `department`
--
ALTER TABLE `department`
  ADD PRIMARY KEY (`department_id`),
  ADD KEY `lecturer_id` (`lecturer_id`) USING BTREE;

--
-- Indexes for table `feedback`
--
ALTER TABLE `feedback`
  ADD PRIMARY KEY (`feedback_id`),
  ADD KEY `user_id` (`user_id`),
  ADD KEY `course_id` (`course_id`);

--
-- Indexes for table `grade_definitions`
--
ALTER TABLE `grade_definitions`
  ADD PRIMARY KEY (`grade_id`);

--
-- Indexes for table `scores`
--
ALTER TABLE `scores`
  ADD PRIMARY KEY (`score_id`),
  ADD KEY `student_id` (`student_id`),
  ADD KEY `course_id` (`course_id`);

--
-- Indexes for table `score_mark`
--
ALTER TABLE `score_mark`
  ADD PRIMARY KEY (`mark_ID`),
  ADD KEY `fk_score_id` (`score_id`),
  ADD KEY `fk_score_type_id` (`score_type`);

--
-- Indexes for table `score_types`
--
ALTER TABLE `score_types`
  ADD PRIMARY KEY (`score_type_id`);

--
-- Indexes for table `students`
--
ALTER TABLE `students`
  ADD PRIMARY KEY (`student_id`),
  ADD UNIQUE KEY `matrix_number` (`matrix_number`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `unique_username` (`username`),
  ADD UNIQUE KEY `unique_email` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `courses`
--
ALTER TABLE `courses`
  MODIFY `course_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `department`
--
ALTER TABLE `department`
  MODIFY `department_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `feedback`
--
ALTER TABLE `feedback`
  MODIFY `feedback_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;

--
-- AUTO_INCREMENT for table `grade_definitions`
--
ALTER TABLE `grade_definitions`
  MODIFY `grade_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

--
-- AUTO_INCREMENT for table `scores`
--
ALTER TABLE `scores`
  MODIFY `score_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=33;

--
-- AUTO_INCREMENT for table `score_mark`
--
ALTER TABLE `score_mark`
  MODIFY `mark_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=114;

--
-- AUTO_INCREMENT for table `score_types`
--
ALTER TABLE `score_types`
  MODIFY `score_type_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `user_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=45;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `course_lecturer`
--
ALTER TABLE `course_lecturer`
  ADD CONSTRAINT `course_lecturer_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `courses` (`course_id`),
  ADD CONSTRAINT `course_lecturer_ibfk_2` FOREIGN KEY (`lecturer_id`) REFERENCES `users` (`user_id`);

--
-- Constraints for table `department`
--
ALTER TABLE `department`
  ADD CONSTRAINT `department_ibfk_1` FOREIGN KEY (`lecturer_id`) REFERENCES `users` (`user_id`);

--
-- Constraints for table `feedback`
--
ALTER TABLE `feedback`
  ADD CONSTRAINT `feedback_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`),
  ADD CONSTRAINT `feedback_ibfk_2` FOREIGN KEY (`course_id`) REFERENCES `courses` (`course_id`);

--
-- Constraints for table `scores`
--
ALTER TABLE `scores`
  ADD CONSTRAINT `scores_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `students` (`student_id`),
  ADD CONSTRAINT `scores_ibfk_2` FOREIGN KEY (`course_id`) REFERENCES `courses` (`course_id`);

--
-- Constraints for table `score_mark`
--
ALTER TABLE `score_mark`
  ADD CONSTRAINT `fk_score_id` FOREIGN KEY (`score_id`) REFERENCES `scores` (`score_id`),
  ADD CONSTRAINT `fk_score_type_id` FOREIGN KEY (`score_type`) REFERENCES `score_types` (`score_type_id`);

--
-- Constraints for table `students`
--
ALTER TABLE `students`
  ADD CONSTRAINT `students_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `users` (`user_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

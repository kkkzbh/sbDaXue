

CREATE DATABASE bc;

USE bc;

CREATE TABLE `problems` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增题目ID',
    `title` VARCHAR(100) NOT NULL COMMENT '题目标题（含编号+名称）',
    `description` MEDIUMTEXT NOT NULL COMMENT '题目描述',
    `solution1` TEXT DEFAULT NULL COMMENT '题解1',
    `solution2` TEXT DEFAULT NULL COMMENT '题解2',
    `url` VARCHAR(255) DEFAULT NULL COMMENT '题目链接',
    `accept_rate` DECIMAL(5,4) DEFAULT NULL COMMENT '通过率（0.0000–1.0000 之间）',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '最后更新时间',
    PRIMARY KEY (`id`),
    KEY `idx_title` (`title`),
    KEY `idx_accept_rate` (`accept_rate`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '算法习题题库表';

CREATE TABLE `problem_tags` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `problem_id` INT UNSIGNED NOT NULL COMMENT '题目ID',
    `tag` VARCHAR(50) NOT NULL COMMENT '标签名称',
    `tag_type` ENUM('core', 'sub') DEFAULT 'core' COMMENT '标签类型：核心标签或子标签',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_problem_tag` (`problem_id`, `tag`),
    KEY `idx_tag` (`tag`),
    KEY `idx_tag_type` (`tag_type`),
    CONSTRAINT `fk_problem_tags_problem_id` FOREIGN KEY (`problem_id`) REFERENCES `problems` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '题目标签关联表';

CREATE TABLE `learning_patterns` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `student_name` VARCHAR(50) NOT NULL COMMENT '学生姓名',
    `knowledge_point` VARCHAR(50) NOT NULL COMMENT '知识点名称',
    `pattern_value` DECIMAL(5,4) NOT NULL COMMENT '学习模式强度（0-1）',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    KEY `idx_student_id` (`student_id`),
    KEY `idx_knowledge_point` (`knowledge_point`),
    KEY `idx_reference_date` (`reference_date`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='学生学习模式表';

CREATE TABLE `learning_pattern_details` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `pattern_id` INT UNSIGNED NOT NULL COMMENT '关联的学习模式ID',
    `detail_type` VARCHAR(30) NOT NULL COMMENT '详情类型',
    `detail_value` TEXT DEFAULT NULL COMMENT '详情值',
    PRIMARY KEY (`id`),
    KEY `idx_pattern_id` (`pattern_id`),
    KEY `idx_detail_type` (`detail_type`),
    CONSTRAINT `fk_pattern_details_pattern_id` FOREIGN KEY (`pattern_id`) REFERENCES `learning_patterns` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='学习模式详情表';

CREATE TABLE `learning_patterns` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `student_name` VARCHAR(50) NOT NULL COMMENT '学生姓名',
    `knowledge_point` VARCHAR(50) NOT NULL COMMENT '知识点名称',
    `pattern_value` DECIMAL(5,4) NOT NULL COMMENT '学习模式强度（0-1）',
    `pattern_type` VARCHAR(50) DEFAULT NULL COMMENT '学习模式类型（如集中、分散、规律、突击等）',
    `learning_style` VARCHAR(50) DEFAULT NULL COMMENT '学习风格',
    `time_preference` VARCHAR(50) DEFAULT NULL COMMENT '时间偏好',
    `consistency_level` DECIMAL(5,4) DEFAULT NULL COMMENT '一致性水平（0-1）',
    `adaptability` DECIMAL(5,4) DEFAULT NULL COMMENT '适应性（0-1）',
    `notes` TEXT DEFAULT NULL COMMENT '其他备注',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    KEY `idx_student_id` (`student_id`),
    KEY `idx_knowledge_point` (`knowledge_point`),
    KEY `idx_pattern_type` (`pattern_type`),
    KEY `idx_reference_date` (`reference_date`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='学生学习模式表';

CREATE TABLE `code_quality_metrics` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `student_name` VARCHAR(50) NOT NULL COMMENT '学生姓名',
    `metric_name` VARCHAR(50) NOT NULL COMMENT '指标名称',
    `metric_value` DECIMAL(5,4) NOT NULL COMMENT '指标值（0-1）',
    `metric_description` TEXT DEFAULT NULL COMMENT '指标描述',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    KEY `idx_student_id` (`student_id`),
    KEY `idx_metric_name` (`metric_name`),
    KEY `idx_reference_date` (`reference_date`)
) ENGINE=InnoDB
  DEFAULT CHARSET=utf8mb4
  COLLATE=utf8mb4_unicode_ci
    COMMENT='学生代码质量指标表';

CREATE TABLE `student_error_patterns` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `student_name` VARCHAR(50) NOT NULL COMMENT '学生姓名',
    `avg_attempts_before_success` DECIMAL(5,2) DEFAULT NULL COMMENT '平均尝试次数',
    `learning_trend` VARCHAR(30) DEFAULT NULL COMMENT '学习趋势',
    `correct_rate_change` DECIMAL(5,4) DEFAULT NULL COMMENT '正确率变化',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '分析时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_student_id_date` (`student_id`, `reference_date`),
    KEY `idx_student_id` (`student_id`),
    KEY `idx_learning_trend` (`learning_trend`)
) ENGINE=InnoDB
  DEFAULT CHARSET=utf8mb4
  COLLATE=utf8mb4_unicode_ci
    COMMENT='学生错误模式总表';

CREATE TABLE `error_distributions` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `pattern_id` INT UNSIGNED NOT NULL COMMENT '关联的错误模式ID',
    `distribution_type` ENUM('error_type', 'error_category', 'error_severity') NOT NULL COMMENT '分布类型',
    `item_name` VARCHAR(50) NOT NULL COMMENT '项目名称',
    `frequency` DECIMAL(5,4) NOT NULL COMMENT '频率（0-1）',
    `recovery_time` INT DEFAULT NULL COMMENT '恢复时间（秒）',
    `to_correct_rate` DECIMAL(5,4) DEFAULT NULL COMMENT '转为正确的比率',
    PRIMARY KEY (`id`),
    KEY `idx_pattern_id` (`pattern_id`),
    KEY `idx_distribution_type` (`distribution_type`),
    CONSTRAINT `fk_error_dist_pattern_id` FOREIGN KEY (`pattern_id`) REFERENCES `student_error_patterns` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB
  DEFAULT CHARSET=utf8mb4
  COLLATE=utf8mb4_unicode_ci
    COMMENT='错误分布表';

CREATE TABLE `error_sequences` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `pattern_id` INT UNSIGNED NOT NULL COMMENT '关联的错误模式ID',
    `sequence` VARCHAR(255) NOT NULL COMMENT '错误序列',
    `frequency` INT NOT NULL COMMENT '出现频率',
    PRIMARY KEY (`id`),
    KEY `idx_pattern_id` (`pattern_id`),
    CONSTRAINT `fk_error_seq_pattern_id` FOREIGN KEY (`pattern_id`) REFERENCES `student_error_patterns` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB
  DEFAULT CHARSET=utf8mb4
  COLLATE=utf8mb4_unicode_ci
    COMMENT='错误序列表';

CREATE TABLE `knowledge_error_patterns` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `knowledge_point` VARCHAR(50) NOT NULL COMMENT '知识点名称',
    `error_rate` DECIMAL(5,4) NOT NULL COMMENT '错误率（0-1）',
    `correct_rate` DECIMAL(5,4) NOT NULL COMMENT '正确率（0-1）',
    `high_severity_rate` DECIMAL(5,4) DEFAULT NULL COMMENT '高严重度错误率',
    `most_common_error` VARCHAR(50) DEFAULT NULL COMMENT '最常见错误类型',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '分析时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_kp_date` (`knowledge_point`, `reference_date`),
    KEY `idx_knowledge_point` (`knowledge_point`),
    KEY `idx_error_rate` (`error_rate`)
) ENGINE=InnoDB
  DEFAULT CHARSET=utf8mb4
  COLLATE=utf8mb4_unicode_ci
    COMMENT='知识点错误模式表';

CREATE TABLE `knowledge_correlation` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `knowledge_point` VARCHAR(50) NOT NULL COMMENT '知识点名称',
    `degree_centrality` DECIMAL(5,4) DEFAULT NULL COMMENT '度中心性（0-1）',
    `weighted_degree` DECIMAL(10,4) DEFAULT NULL COMMENT '加权度中心性',
    `closeness` DECIMAL(5,4) DEFAULT NULL COMMENT '接近中心性',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_knowledge_date` (`knowledge_point`, `reference_date`),
    KEY `idx_degree_centrality` (`degree_centrality`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='知识点关联基础表';

CREATE TABLE `knowledge_hierarchy` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `knowledge_point` VARCHAR(50) NOT NULL COMMENT '知识点名称',
    `depth` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '层次深度',
    `parent_point` VARCHAR(50) DEFAULT NULL COMMENT '父知识点',
    `top_category` VARCHAR(50) DEFAULT NULL COMMENT '顶级类别',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_knowledge_date` (`knowledge_point`, `reference_date`),
    KEY `idx_top_category` (`top_category`),
    KEY `idx_parent_point` (`parent_point`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='知识点层次特征表';

CREATE TABLE `knowledge_path` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `hierarchy_id` INT UNSIGNED NOT NULL COMMENT '关联的层次特征ID',
    `path_index` INT UNSIGNED NOT NULL COMMENT '路径中的索引位置',
    `path_node` VARCHAR(50) NOT NULL COMMENT '路径节点知识点',
    PRIMARY KEY (`id`),
    KEY `idx_hierarchy_id` (`hierarchy_id`),
    CONSTRAINT `fk_path_hierarchy_id` FOREIGN KEY (`hierarchy_id`) REFERENCES `knowledge_hierarchy` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='知识点路径表';

CREATE TABLE `knowledge_relations` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `knowledge_from` VARCHAR(50) NOT NULL COMMENT '源知识点',
    `knowledge_to` VARCHAR(50) NOT NULL COMMENT '目标知识点',
    `relation_type` ENUM('prerequisite', 'related') NOT NULL COMMENT '关系类型: 前置或相关',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_relation` (`knowledge_from`, `knowledge_to`, `relation_type`, `reference_date`),
    KEY `idx_knowledge_from` (`knowledge_from`),
    KEY `idx_knowledge_to` (`knowledge_to`),
    KEY `idx_relation_type` (`relation_type`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='知识点关系表';

CREATE TABLE `knowledge_cooccurrence` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `knowledge_point1` VARCHAR(50) NOT NULL COMMENT '知识点1',
    `knowledge_point2` VARCHAR(50) NOT NULL COMMENT '知识点2',
    `cooccurrence_count` DECIMAL(10,4) NOT NULL DEFAULT 0 COMMENT '共现次数',
    `jaccard_similarity` DECIMAL(5,4) NOT NULL DEFAULT 0 COMMENT 'Jaccard相似度（0-1）',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_points_date` (`knowledge_point1`, `knowledge_point2`, `reference_date`),
    KEY `idx_knowledge_point1` (`knowledge_point1`),
    KEY `idx_knowledge_point2` (`knowledge_point2`),
    KEY `idx_jaccard_similarity` (`jaccard_similarity`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='知识点共现矩阵表';

CREATE TABLE `knowledge_dependency` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `knowledge_point1` VARCHAR(50) NOT NULL COMMENT '知识点1',
    `knowledge_point2` VARCHAR(50) NOT NULL COMMENT '知识点2',
    `correlation_value` DECIMAL(5,4) NOT NULL DEFAULT 0 COMMENT '相关系数（-1到1）',
    `reference_date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '参考日期',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_points_date` (`knowledge_point1`, `knowledge_point2`, `reference_date`),
    KEY `idx_knowledge_point1` (`knowledge_point1`),
    KEY `idx_knowledge_point2` (`knowledge_point2`),
    KEY `idx_correlation_value` (`correlation_value`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT='知识点依赖关系表';

CREATE TABLE `text_features` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `problem_id` INT UNSIGNED NOT NULL,
    `embedding_local` JSON DEFAULT NULL,
    `embedding_deepseek` JSON DEFAULT NULL,
    `keywords` JSON DEFAULT NULL,
    `key_concepts` JSON DEFAULT NULL,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `updated_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_problem_id` (`problem_id`),
    CONSTRAINT `fk_text_features_problem_id` FOREIGN KEY (`problem_id`) REFERENCES `problems` (`id`) ON DELETE CASCADE
);

CREATE TABLE `problem_embeddings` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `problem_id` INT UNSIGNED NOT NULL COMMENT '题目ID',
    `embedding` JSON NOT NULL COMMENT '题目嵌入向量',
    `text_component` JSON DEFAULT NULL COMMENT '文本特征组件',
    `graph_component` JSON DEFAULT NULL COMMENT '图结构特征组件',
    `stats_component` JSON DEFAULT NULL COMMENT '统计特征组件',
    `deepseek_component` JSON DEFAULT NULL COMMENT 'DeepSeek特征组件',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_problem_id` (`problem_id`),
    CONSTRAINT `fk_problem_embeddings_problem_id` FOREIGN KEY (`problem_id`) REFERENCES `problems` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '题目嵌入向量表';

CREATE TABLE `student_embeddings` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `student_name` VARCHAR(50) NOT NULL COMMENT '学生姓名',
    `embedding` JSON NOT NULL COMMENT '学生统一嵌入向量（256维）',
    `sequence_component` JSON DEFAULT NULL COMMENT '序列模型组件向量',
    `transformer_component` JSON DEFAULT NULL COMMENT '时序Transformer组件向量',
    `gnn_component` JSON DEFAULT NULL COMMENT '知识图谱GNN组件向量',
    `code_quality_component` JSON DEFAULT NULL COMMENT '代码质量组件向量',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '最后更新时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_student_id` (`student_id`),
    KEY `idx_updated_at` (`updated_at`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '学生嵌入向量表';

CREATE TABLE `student_embedding_similarities` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id1` VARCHAR(20) NOT NULL COMMENT '学生1学号',
    `student_id2` VARCHAR(20) NOT NULL COMMENT '学生2学号',
    `similarity_score` DECIMAL(5,4) NOT NULL COMMENT '相似度分数(0-1)',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '最后更新时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_student_pair` (`student_id1`, `student_id2`),
    KEY `idx_student_id1` (`student_id1`),
    KEY `idx_student_id2` (`student_id2`),
    KEY `idx_similarity` (`similarity_score`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '学生嵌入相似度表';

CREATE TABLE `student_embedding_clusters` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `cluster_id` INT NOT NULL COMMENT '聚类分组ID',
    `cluster_description` VARCHAR(255) DEFAULT NULL COMMENT '聚类分组描述',
    `distance_to_centroid` DECIMAL(10,6) DEFAULT NULL COMMENT '到聚类中心的距离',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_student_id` (`student_id`),
    KEY `idx_cluster_id` (`cluster_id`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '学生嵌入聚类分组表';

CREATE TABLE `student_embedding_history` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `embedding` JSON NOT NULL COMMENT '学生嵌入向量',
    `snapshot_date` DATE NOT NULL COMMENT '快照日期',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_student_date` (`student_id`, `snapshot_date`),
    KEY `idx_student_id` (`student_id`),
    KEY `idx_snapshot_date` (`snapshot_date`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '学生嵌入向量历史表';

CREATE TABLE `student_embedding_update_logs` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '主键，自增ID',
    `student_id` VARCHAR(20) NOT NULL COMMENT '学生学号',
    `update_type` ENUM('initial', 'sequence', 'transformer', 'gnn', 'code_quality', 'full') NOT NULL COMMENT '更新类型',
    `update_details` JSON DEFAULT NULL COMMENT '更新详情',
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    PRIMARY KEY (`id`),
    KEY `idx_student_id` (`student_id`),
    KEY `idx_update_type` (`update_type`),
    KEY `idx_created_at` (`created_at`)
) ENGINE=InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci
    COMMENT = '学生嵌入向量更新日志表';


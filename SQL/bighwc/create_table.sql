

USE k;

CREATE TABLE VIP_Level (
    vip_level_id   INT AUTO_INCREMENT PRIMARY KEY,
    vip_code       VARCHAR(18) NOT NULL UNIQUE,    -- e.g. 'Regular','Gold','Platinum'
    description    VARCHAR(36),
    discount_rate  DECIMAL(3,2) NOT NULL           -- e.g. 0.80
);

CREATE TABLE Person (
    person_id     INT AUTO_INCREMENT PRIMARY KEY,
    name          VARCHAR(8)  NOT NULL,
    sex           ENUM('M','F','Other') NOT NULL,
    age           TINYINT      NOT NULL,
    id_number     VARCHAR(18)  NOT NULL UNIQUE, -- 身份证号
    phone         VARCHAR(18)  NOT NULL,
    vip_level_id  INT          NOT NULL,
    created_at    DATETIME     DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (vip_level_id) REFERENCES VIP_Level(vip_level_id)
);


CREATE TABLE Room_State (
    state_id   INT AUTO_INCREMENT PRIMARY KEY,
    state_code VARCHAR(36) NOT NULL UNIQUE,        -- e.g. 'Available','Reserved','Occupied'
    description VARCHAR(64)
);

CREATE TABLE Audit_Status (
    audit_status_id INT AUTO_INCREMENT PRIMARY KEY,
    status_code     VARCHAR(36) NOT NULL UNIQUE,   -- e.g. 'Pending','Approved','Rejected'
    description     VARCHAR(64)
);

CREATE TABLE Room_Type (
    type_id    INT AUTO_INCREMENT PRIMARY KEY,
    type_code  VARCHAR(16) NOT NULL UNIQUE,        -- e.g. 'Single','Double','Suite'
    description VARCHAR(64)
);

CREATE TABLE Room (
    room_id         INT AUTO_INCREMENT PRIMARY KEY,
    room_no         VARCHAR(16)   NOT NULL UNIQUE,
    type_id         INT           NOT NULL,
    state_id        INT           NOT NULL,
    location        VARCHAR(16),
    price           DECIMAL(10,2) NOT NULL,
    create_datatime DATETIME      DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (type_id)  REFERENCES Room_Type(type_id),
    FOREIGN KEY (state_id) REFERENCES Room_State(state_id)
);

CREATE TABLE StayHistory (
    history_id   INT AUTO_INCREMENT PRIMARY KEY,
    person_id    INT NOT NULL,
    room_id      INT NOT NULL,
    stay_date    DATE    NOT NULL,
    stay_price   DECIMAL(10,2) NOT NULL,
    reserve_time DATETIME,              -- 如果需要记录
    FOREIGN KEY (person_id) REFERENCES Person(person_id),
    FOREIGN KEY (room_id)   REFERENCES Room(room_id)
);

CREATE TABLE Reservation (
    reservation_id   INT AUTO_INCREMENT PRIMARY KEY,
    person_id        INT NOT NULL,
    room_id          INT NOT NULL,
    price            DECIMAL(10,2) NOT NULL,
    remark           VARCHAR(36),
    audit_status_id  INT DEFAULT NULL,
    review_reply     VARCHAR(36),
    reserve_at       DATETIME  NOT NULL,           -- 预订日期+时间
    FOREIGN KEY (person_id)       REFERENCES Person(person_id),
    FOREIGN KEY (room_id)         REFERENCES Room(room_id),
    FOREIGN KEY (audit_status_id) REFERENCES Audit_Status(audit_status_id)
);

CREATE TABLE Extension (
    extension_id   INT AUTO_INCREMENT PRIMARY KEY,
    reservation_id INT NOT NULL,
    price          DECIMAL(10,2) NOT NULL,
    remark         VARCHAR(36),
    audit_status_id INT DEFAULT NULL,
    review_reply    VARCHAR(36),
    extend_at      DATETIME NOT NULL,
    FOREIGN KEY (reservation_id) REFERENCES Reservation(reservation_id),
    FOREIGN KEY (audit_status_id) REFERENCES Audit_Status(audit_status_id)
);

CREATE TABLE CheckOut (
    checkout_id    INT AUTO_INCREMENT PRIMARY KEY,
    reservation_id INT NOT NULL,
    price          DECIMAL(10,2) NOT NULL,
    remark         VARCHAR(36),
    audit_status_id INT DEFAULT NULL,
    review_reply    VARCHAR(36),
    checkout_at    DATETIME NOT NULL,
    FOREIGN KEY (reservation_id) REFERENCES Reservation(reservation_id),
    FOREIGN KEY (audit_status_id) REFERENCES Audit_Status(audit_status_id)
);


-- CreateTable
CREATE TABLE "PetState" (
    "id" SERIAL NOT NULL,
    "userId" INTEGER NOT NULL,
    "hunger" INTEGER NOT NULL DEFAULT 50,
    "happiness" INTEGER NOT NULL DEFAULT 50,
    "cleanliness" INTEGER NOT NULL DEFAULT 50,
    "energy" INTEGER NOT NULL DEFAULT 50,
    "lastFed" TIMESTAMP(3),
    "lastPlayed" TIMESTAMP(3),
    "lastCleaned" TIMESTAMP(3),
    "lastSlept" TIMESTAMP(3),
    "updatedAt" TIMESTAMP(3) NOT NULL,

    CONSTRAINT "PetState_pkey" PRIMARY KEY ("id")
);

-- CreateIndex
CREATE UNIQUE INDEX "PetState_userId_key" ON "PetState"("userId");

-- AddForeignKey
ALTER TABLE "PetState" ADD CONSTRAINT "PetState_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

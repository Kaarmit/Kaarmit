-- AlterTable
ALTER TABLE "User" ADD COLUMN     "background" TEXT NOT NULL DEFAULT '/backgrounds/city.png',
ADD COLUMN     "cat" TEXT NOT NULL DEFAULT 'beigecat',
ADD COLUMN     "color" TEXT NOT NULL DEFAULT '#FF69B4';
